//
// Created by Cisco on 31/05/2024.
//

#include "Launcher.hpp"

using namespace ParticleSystem;

static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

Launcher::Launcher()
{
    glfwSetErrorCallback(glfw_error_callback);
    if(glfwInit() == 0)
        exit(1);

// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    const char* glsl_version = "#version 300 es";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#else
    const char* glsl_version = "#version 430";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // 3.0+ only
#endif

    // According to init windowSize
    _displayWidth = _windowWidth;
    _displayHeight = _windowHeight;


    // Create window with graphics context
//    std::string windowTitle = PROJECT_NAME.data();
    std::string windowTitle = "Particle System";
    windowTitle += " (U to show/hide UI)";
    _window = glfwCreateWindow(_displayWidth, _displayHeight, windowTitle.c_str(), nullptr, nullptr);
    if (_window == nullptr)
        exit(1);
    glfwMakeContextCurrent(_window);
    //    glfwSwapInterval(1); // Enable vsync
    glfwSwapInterval(0); // Disable vsync
    //    glfwWindowHint(GLFW_REFRESH_RATE, 0); // Disable refresh rate
    //    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE); // Disable refresh rate
    //    glfwWindowHint(GLFW_REFRESH_RATE, 60);

    // Callbacks
    glfwSetWindowUserPointer(_window, this);
    glfwSetKeyCallback(_window, InputManager::key_callback);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
//    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
//    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
//    ImGuiStyle& style = ImGui::GetStyle();
//    if ((io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) != 0)
//    {
//        style.WindowRounding = 0.0F;
//        style.Colors[ImGuiCol_WindowBg].w = 1.0F;
//    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup OpenGL state
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Same line as above but with C++ string
    std::cout << "OpenGL vendor: " << _getOpenGLVendor() << std::endl
              << "OpenGL version: " << _getOpenGLVersion() << std::endl
              << "GLSL version: " << _getGLSLVersion() << std::endl
              << "GLFW version: " << _getGLFWVersion() << std::endl
              << "Glad version: " << _getGladVersion() << std::endl
              << "ImGui version: " << _getImGuiVersion() << std::endl
              << "GLM version: " << _getGLMVersion() << std::endl;

}

Launcher::~Launcher() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Launcher::toggleUiVisibility()
{
    isUiVisible = !isUiVisible;
}

void Launcher::clearScreen() const {
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto Launcher::isMinimized() const -> bool {
    return glfwGetWindowAttrib(_window, GLFW_ICONIFIED) != 0;
}

void Launcher::_calculateMouseMovement(const double& xMouse, const double& yMouse, double& xMovement,
                                                       double& yMovement) {
    static double lastMouseX = 0.0;
    static double lastMouseY = 0.0;

    xMovement = xMouse - lastMouseX;
    yMovement = lastMouseY - yMouse;

    lastMouseX = xMouse;
    lastMouseY = yMouse;
}

auto Launcher::_projectMouse(const double& xMouse, const double& yMouse) -> glm::vec3 {
    // Convert the mouse coordinates from screen space to NDC space
    float const normalized_x = (2.0F * static_cast<float>(xMouse)) / static_cast<float>(_displayWidth) - 1.0F;
    float const normalized_y = 1.0F - (2.0F * static_cast<float>(yMouse)) / static_cast<float>(_displayHeight);

    // Create a vector representing the mouse coordinates in NDC space
    glm::vec4 const mouse_ndc(normalized_x, normalized_y, -1.0F, 1.0F);

    // Convert the mouse coordinates from NDC space to world space
    glm::mat4 const inverse_projection = glm::inverse(_scene->camera.getProjectionMatrix());
    glm::mat4 const inverse_view = glm::inverse(_scene->camera.getViewMatrix());
    glm::vec4 mouse_world = inverse_projection * mouse_ndc;
    mouse_world = mouse_world / mouse_world.w;
    mouse_world = inverse_view * mouse_world;

    // Calculate the direction from the camera position to the mouse position
    glm::vec3 const camera_to_mouse = glm::normalize(glm::vec3(mouse_world) - _scene->camera.position);

    // Use the direction to update the position of an object in the 3D environment
    return _scene->camera.position + camera_to_mouse * attractorDistance;
}

auto Launcher::_getOpenGLVendor() -> std::string_view
{
    return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
}

auto Launcher::_getOpenGLVersion() -> std::string_view
{
    return reinterpret_cast<const char*>(glGetString(GL_VERSION));
}

auto Launcher::_getGLSLVersion() -> std::string_view
{
    // TODO:
//    return reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
    return "Not yet implemented!";

}

auto Launcher::_getGLFWVersion() -> std::string
{
    return std::to_string(GLFW_VERSION_MAJOR) + "." + std::to_string(GLFW_VERSION_MINOR) + "." +
           std::to_string(GLFW_VERSION_REVISION);
}

auto Launcher::_getGladVersion() -> std::string_view
{
    return "0.1.36";
}

auto Launcher::_getImGuiVersion() -> std::string
{
    return IMGUI_VERSION;
}

auto Launcher::_getGLMVersion() -> std::string
{
    return std::to_string(GLM_VERSION_MAJOR) + "." + std::to_string(GLM_VERSION_MINOR) + "." +
           std::to_string(GLM_VERSION_PATCH);
}