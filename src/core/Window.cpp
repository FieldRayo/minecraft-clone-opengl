#include "Window.h"

#include <iostream>

#include <glad/glad.h>

#include "Settings.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(int w, int h, std::string wn) : m_width(w), m_height(h), m_name(wn) { }
Window::Window(std::string wn) : m_name(wn) { }

bool Window::isOpen() const {
    return !glfwWindowShouldClose(m_window);
}

GLFWwindow* Window::GetHandle() const {
    return m_window;
}

void Window::RequestClose() {
    glfwSetWindowShouldClose(m_window, true);
}

bool Window::Init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif // __APPLE__

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    if (!monitor) {
        std::cerr << "Failed to get primary monitor!" << std::endl;
        return false;
    }
    
    m_mode = glfwGetVideoMode(monitor);

    if (!m_mode) {
        std::cerr << "Failed to get video mode!" << std::endl;
        return false;
    }
    
    if (!m_width || !m_height) {
        m_width = m_mode->width;
        m_height = m_mode->height;
    }

    auto& s = Settings::Get();
    m_window = glfwCreateWindow(
        s.windowWidth,
        s.windowHeight,
        s.windowTitle.c_str(),
        nullptr,
        nullptr
    );

    if (!m_window) {
        std::cerr << "Failed to create window: " << m_name << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}

void Window::SwapBuffers() { glfwSwapBuffers(m_window); }

void Window::PollEvents() { glfwPollEvents(); }

