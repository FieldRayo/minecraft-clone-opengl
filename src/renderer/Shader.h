#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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

    // Uniforms
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);

    void setVec3(const std::string& name, const glm::vec3& value);
    void setMat4(const std::string& name, const glm::mat4& value);
private:
    char* readFile(const std::string& path);
    unsigned int compileShader(const ShaderSource& ss);
    int getUniformLocation(const std::string& name);
};

