#pragma once

#include <vector>
#include <cstdint>
#include <iostream>

#include "Chunk.h"

class VertexArray;
class VertexBuffer;
class IndexBuffer;

class Renderer;
class Camera;

enum class Direction { Right, Left, Top, Bottom, Front, Back };

class ChunkMesh{
    std::vector<float> m_vertices;
    std::vector<uint32_t> m_indices;
    uint32_t offset = 0;

    std::unique_ptr<VertexArray> m_vao;
    
    VertexBuffer* m_ref_vbo = nullptr;
    IndexBuffer* m_ref_ibo = nullptr;
public:
    ChunkMesh();
    ~ChunkMesh();

    const std::vector<float>& Getm_vertices() const { return m_vertices; }
    const std::vector<uint32_t>& Getm_indices() const { return m_indices; }

    void Draw(Renderer& renderer, Camera& camera);

    void Build(const ChunkContext& chunkContext);
    void Update(const ChunkContext& chunkContext);
private:
    void GenerateGeometry(const ChunkContext& chunkContext);

    bool ShouldRenderFace(const ChunkContext& ctx, int32_t x, int32_t y, int32_t z, Direction direction);
    void AddFace(float x, float y, float z, Direction direction);
};
