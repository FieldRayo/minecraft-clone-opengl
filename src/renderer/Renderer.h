#pragma once

#include <memory>

#include "Shader.h"
#include "VertexArray.h"
#include "core/Camera.h"

// Forward declarations
class Shader;

class Renderer {
    std::unique_ptr<Shader> m_shader;
public:
    Renderer();
    ~Renderer();
    
    void SetShader(std::unique_ptr<Shader> shader) { m_shader = std::move(shader); }
    void Draw(const VertexArray& vao, const Camera& camera);
private:
};
