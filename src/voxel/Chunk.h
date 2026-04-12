#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include <iostream>

#include "Block.h"

class Chunk {
    Block blocks[17][17][256];
public:
    Chunk() = default;
    ~Chunk() = default;

    const Block& GetBlock(uint32_t x, uint32_t y, uint32_t z) const { return blocks[x][z][y]; }
    void SetBlock(const Block& block, uint32_t x, uint32_t y, uint32_t z) { blocks[x][z][y] = block; }
};

