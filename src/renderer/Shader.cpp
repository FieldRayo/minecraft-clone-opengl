#include "Shader.h"

#include <iostream>
#include <fstream>

#include "glad/glad.h"

Shader::Shader(const std::vector<ShaderSource>& shaders) {
    
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

void Shader::use() const {

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
