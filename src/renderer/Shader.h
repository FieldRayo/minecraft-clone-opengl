#pragma once

#include <vector>

#include "GLFW/glfw3.h"

struct ShaderSoruce {
    unsigned int type;
    std::string path;
};

class Shader {
public:
    Shader(const std::vector<ShaderSource>& shaders);
    ~Shader();
};
