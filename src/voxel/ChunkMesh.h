#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include "Chunk.h"
#include "renderer/Mesh.h"

class VertexArray;
class VertexBuffer;
class IndexBuffer;
class Texture;

class Renderer;
class Camera;

enum class Direction { Right, Left, Top, Bottom, Front, Back };

class ChunkMesh {
    std::unique_ptr<ChunkContext> m_chunkContext;

    std::vector<ACE::Vertex> m_vertices;
    std::vector<uint32_t> m_indices;
    uint32_t m_offset=0;
public:
    ChunkMesh();
    ChunkMesh(const ChunkContext& ctx);
    ~ChunkMesh();
    
    void Build();
    void Update();
    void ClearCPU();

    void SetChunk(const ChunkContext& ctx) { m_chunkContext = std::make_unique<ChunkContext>(ctx); }

    const std::vector<ACE::Vertex>& GetVertices() const { return m_vertices; }
    const std::vector<uint32_t>& GetIndices() const { return m_indices; }
private:
    void GenerateGeometry();

    bool ShouldRenderFace(int32_t x, int32_t y, int32_t z, Direction direction);
    void AddFace(float x, float y, float z, Direction direction, Block block);
};
