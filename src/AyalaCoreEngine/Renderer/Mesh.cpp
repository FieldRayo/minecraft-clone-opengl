#include "Mesh.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"

namespace ACE {
    
Mesh::Mesh() {
    m_vao = std::make_unique<VertexArray>();
}

Mesh::~Mesh() {
    ClearGPU();
}

void Mesh::Upload(const std::vector<Vertex>& vertices,
            const std::vector<uint32_t>& indices) {

    m_indices = indices.size();
    
    auto vbo = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex));
    auto ibo = std::make_unique<IndexBuffer>(indices.data(), m_indices);

    m_ref_vbo = vbo.get();
    m_ref_ibo = ibo.get();

    BufferLayout layout;
    layout.Push<glm::vec3>("aPos");

    m_vao->AddVertexBuffer(std::move(vbo), layout);
    m_vao->SetIndexBuffer(std::move(ibo));
}

void Mesh::Draw() const {
}

void Mesh::ClearGPU() {
    m_vao->UnBind();
    m_ref_vbo = nullptr;
    m_ref_ibo = nullptr;
}

void Mesh::Bind() const {
    m_vao->Bind();
}

}

