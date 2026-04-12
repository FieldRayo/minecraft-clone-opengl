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

    void Draw(const std::unique_ptr<VertexArray>& vao, const Shader& shader, const Camera& camera);
private:
};
