#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include <iostream>

#include "Block.h"

const uint32_t CHUNK_SIZE_X = 16;
const uint32_t CHUNK_SIZE_Y = 32;
const uint32_t CHUNK_SIZE_Z = 16;

class Chunk {
    Block blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];
public:
    Chunk() = default;
    ~Chunk() = default;

    const Block& GetBlock(uint32_t x, uint32_t y, uint32_t z) const { return blocks[x][y][z]; }
    void SetBlock(Block block, uint32_t x, uint32_t y, uint32_t z) { blocks[x][y][z] = block; }
};

