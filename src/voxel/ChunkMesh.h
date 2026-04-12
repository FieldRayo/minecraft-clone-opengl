#pragma once

#include <vector>
#include <cstdint>
#include <iostream>

#include "Chunk.h"
#include "renderer/VertexArray.h"

class ChunkMesh{
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    uint32_t offset = 0;

    std::unique_ptr<VertexArray> vao;
public:
    ChunkMesh() = default;
    ~ChunkMesh() = default;

    const std::vector<float>& GetVertices() const { return vertices; }
    const std::vector<uint32_t>& GetIndices() const { return indices; }

    void Build(const Chunk& chunk);

    void AddFaceRight(float x, float y, float z);
    void AddFaceLeft(float x, float y, float z);
    void AddFaceTop(float x, float y, float z);
    void AddFaceBottom(float x, float y, float z);
    void AddFaceFront(float x, float y, float z);
    void AddFaceBack(float x, float y, float z);
};
