#include "Renderer.h"

#include <memory>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "IndexBuffer.h"

Renderer::Renderer() = default;

Renderer::~Renderer() = default;

void Renderer::Draw(const VertexArray& vao, const Camera& camera) {
    m_shader->use();
    vao.Bind();

    const glm::mat4 view = camera.GetViewMatrix();
    const glm::mat4 projection = camera.GetProjectionMatrix();

    m_shader->setMat4("uView", view);
    m_shader->setMat4("uProjection", projection);

    glDrawElements(
        GL_TRIANGLES,
        vao.GetIndexBuffer()->GetCount(),
        GL_UNSIGNED_INT,
        nullptr
    );
}
