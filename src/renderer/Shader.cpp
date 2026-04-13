#include "Shader.h"

#include <iostream>
#include <fstream>

#include <glad/glad.h>

Shader::Shader(const std::vector<ShaderSource>& shaders) {
    std::vector<unsigned int> compileShaders;
    for(auto& s : shaders)
        compileShaders.push_back(CompileShader(s));       

    ID = glCreateProgram();
    for(auto& cs : compileShaders)
        glAttachShader(ID, cs);
    glLinkProgram(ID);

    int success;
    char infoLog[512];

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "ERROR:SHADER::LINKING_FAILED" << std::endl << infoLog << std::endl;
    }
    
    for(auto& cs : compileShaders)
        glDeleteShader(cs);
}

Shader::Shader() {
    ID = glCreateProgram();
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

void Shader::use() const {
    glUseProgram(ID);
}

const unsigned int Shader::GetId() const {
    return ID;
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3f(
        glGetUniformLocation(ID, name.c_str()),
        value.x, value.y, value.z
    );
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const {
    glUniformMatrix4fv(
        glGetUniformLocation(ID, name.c_str()),
        1,
        GL_FALSE,
        &value[0][0]
    );
}
char* Shader::readFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    
    if (!file) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return nullptr;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    char* buffer = new char[size+1];
    if (!file.read(buffer, size)) {
        std::cerr << "Failed to read file: " << path << std::endl;
        delete[] buffer;
        return nullptr;
    }

    buffer[size] = '\0';

    return buffer;
}

unsigned int Shader::CompileShader(const ShaderSource& ss) {
    unsigned int shader = glCreateShader(ss.type);
    const char* src = readFile(ss.path);

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
    }

    return shader;
}

int Shader::getUniformLocation(const std::string& name) {
    if (m_uniformCache.find(name) != m_uniformCache.end())
        return m_uniformCache[name];

    int location = glGetUniformLocation(ID, name.c_str());
    m_uniformCache[name] = location;
    return location;
}

