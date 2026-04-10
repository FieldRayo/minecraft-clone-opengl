#pragma once

#include <memory>

// Forward declarations
class Shader;

class Renderer {
    std::unique_ptr<Shader> m_shader;
public:
    Renderer();
    ~Renderer();
private:
    
};
