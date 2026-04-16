#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>
#include <memory>

namespace ACE {
    
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Window {
    GLFWwindow* m_window;
    const GLFWvidmode* m_mode;

    int m_width = 0;
    int m_height = 0;
    std::string m_name;

public:
    Window() = default;
    Window(int w, int h, std::string wn);
    Window(std::string wn);

    ~Window() = default;
    
    bool isOpen() const;
    GLFWwindow* GetHandle() const;
    
    void RequestClose();

    bool Init();
    void SwapBuffers();
    void PollEvents();
private:
};

}

