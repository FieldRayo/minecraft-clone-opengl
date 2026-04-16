#include "Input.h"

namespace ACE {
    
GLFWwindow* Input::s_window = nullptr;

void Input::Init(GLFWwindow* window) {
    s_window = window;
}

bool Input::IsKeyPressed(int key) {
    return glfwGetKey(s_window, key) == GLFW_PRESS;
}

bool Input::IsMouseButtonPressed(int button) {
    return glfwGetMouseButton(s_window, button) == GLFW_PRESS;
}

double Input::GetMouseX() {
    double x, y;
    glfwGetCursorPos(s_window, &x, &y);
    return x;
}

double Input::GetMouseY() {
    double x, y;
    glfwGetCursorPos(s_window, &x, &y);
    return y;
}

}

