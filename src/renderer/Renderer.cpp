#include "Renderer.h"

#include <memory>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "IndexBuffer.h"

Renderer::Renderer() = default;

Renderer::~Renderer() = default;

void Renderer::Draw(const std::unique_ptr<VertexArray>& vao, const Shader& shader, const Camera& camera) {
    shader.use();
    vao->Bind();

    const glm::mat4 view = camera.GetViewMatrix();
    const glm::mat4 projection = camera.GetProjectionMatrix();

    shader.setMat4("uView", view);
    shader.setMat4("uProjection", projection);

    glDrawElements(
        GL_TRIANGLES,
        vao->GetIndexBuffer()->GetCount(),
        GL_UNSIGNED_INT,
        nullptr
    );
}
