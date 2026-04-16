#pragma once

#include <memory>
#include <cstdint>

#include <glm/glm.hpp>

namespace ACE {
    
class VertexArray;
class VertexBuffer;
class IndexBuffer;

struct Vertex {
    glm::vec3 Position;
};

class Mesh {
    std::unique_ptr<VertexArray> m_vao;
    VertexBuffer* m_ref_vbo;
    IndexBuffer* m_ref_ibo;

    uint32_t m_indices = 0;
public:
    Mesh();
    ~Mesh();

    void Upload(const std::vector<Vertex>& vertices,
                const std::vector<uint32_t>& indices);

    void Draw() const;
    void ClearGPU();

    void Bind() const;

    const VertexArray& GetVAO() const { return *m_vao; }
    uint32_t GetIndicesCount() const { return m_indices; }
};

}

