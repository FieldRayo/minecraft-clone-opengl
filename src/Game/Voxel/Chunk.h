#pragma once

#include <vector>
#include <memory>
#include <cstdint>

#include <glm/glm.hpp>

#include "Block.h"

constexpr uint32_t CHUNK_SIZE_X = 16;
constexpr uint32_t CHUNK_SIZE_Y = 64;
constexpr uint32_t CHUNK_SIZE_Z = 16;

class Chunk {
    Block blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];
    glm::ivec2 Position = { 0, 0 }; // Coords
public:
    Chunk();
    Chunk(glm::ivec2 position);
    ~Chunk();

    const Block& GetBlock(uint32_t x, uint32_t y, uint32_t z) const;
    void SetBlock(Block block, uint32_t x, uint32_t y, uint32_t z);

    void SetPosition(const glm::ivec2& position) { Position = position; }
    const glm::ivec2& GetPosition() const { return Position; }
};

