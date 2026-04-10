#pragma once

#include <GLFW/glfw3.h>

class Input {
    static GLFWwindow* s_window;

public:
    static void Init(GLFWwindow* window);

    static bool IsKeyPressed(int key);
    static bool IsMouseButtonPressed(int button);

    static double GetMouseX();
    static double GetMouseY();
};
