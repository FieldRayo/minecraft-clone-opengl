#pragma once

#include <vector>
#include <memory>
#include <cstdint>

#include <glm/glm.hpp>

#include "Block.h"

const uint32_t CHUNK_SIZE_X = 16;
const uint32_t CHUNK_SIZE_Y = 64;
const uint32_t CHUNK_SIZE_Z = 16;

class Chunk {
    Block blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];
    glm::vec3 Position = { 0.0f, 0.0f, 0.0f }; // Cords
public:
    Chunk();
    Chunk(glm::vec3 position);
    ~Chunk();

    const Block& GetBlock(uint32_t x, uint32_t y, uint32_t z) const;
    void SetBlock(Block block, uint32_t x, uint32_t y, uint32_t z);

    const glm::vec3& GetPosition() const;
};

struct ChunkContext{
    const Chunk& Center;
    const Chunk* Right = nullptr;
    const Chunk* Left = nullptr;
    const Chunk* Top = nullptr;
    const Chunk* Bottom = nullptr;
    const Chunk* Front = nullptr;
    const Chunk* Back = nullptr;

    ChunkContext(const Chunk& chunk);
    ~ChunkContext();
};

