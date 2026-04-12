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

    Shader();
    ~Shader();

    void use() const;

    // Uniforms
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setMat4(const std::string& name, const glm::mat4& value) const;
private:
    char* readFile(const std::string& path);
    unsigned int CompileShader(const ShaderSource& ss);
    int getUniformLocation(const std::string& name);
};

