#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

struct ShaderSource {
    unsigned int type;
    std::string path;
};

class Shader {
    unsigned int ID;
    std::unordered_map<std::string, int> m_uniformCache;
public:
    Shader(const std::vector<ShaderSource>& shaders);
    ~Shader();

    void use() const;
private:
    char* readFile(const std::string& path);
    unsigned int compileShader(const ShaderSource& shader);
    int getUniformLocation(const std::string& name);
};

