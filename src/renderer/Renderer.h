#pragma once

#include <memory>

#include "Shader.h"
#include "Mesh.h"
#include "core/Camera.h"

// Forward declarations
class Shader;

class Renderer {
    std::unique_ptr<Shader> m_shader;
public:
    Renderer();
    ~Renderer();
    
    void SetShader(std::unique_ptr<Shader> shader) { m_shader = std::move(shader); }
    const std::unique_ptr<Shader>& GetShader() const { return m_shader; }
    void Draw(const Mesh& mesh, const Camera& camera);
private:
};
