#include "Chunk.h"

Chunk::Chunk() {
    static Block air = Block(0, BlockType::Air); // Default block
    for (uint32_t x = 0; x < CHUNK_SIZE_X; ++x) 
    for (uint32_t y = 0; y < CHUNK_SIZE_Y; ++y)
    for (uint32_t z = 0; z < CHUNK_SIZE_Z; ++z) {
        blocks[x][y][z] = air;
    }

}

Chunk::Chunk(glm::ivec2 position) : Position(position) { 
    static Block air = Block(0, BlockType::Air); // Default block
    for (uint32_t x = 0; x < CHUNK_SIZE_X; ++x) 
    for (uint32_t y = 0; y < CHUNK_SIZE_Y; ++y)
    for (uint32_t z = 0; z < CHUNK_SIZE_Z; ++z) {
        blocks[x][y][z] = air;
    }
}

Chunk::~Chunk() = default;

// --- class: Chunk //

const Block& Chunk::GetBlock(uint32_t x, uint32_t y, uint32_t z) const { 
    static Block air = Block(0, BlockType::Air); // Default block
    if (x >= CHUNK_SIZE_X || y >= CHUNK_SIZE_Y || z >= CHUNK_SIZE_Z)
        return air;

    return blocks[x][y][z];
}

void Chunk::SetBlock(Block block, uint32_t x, uint32_t y, uint32_t z) {
    if (x >= CHUNK_SIZE_X || y >= CHUNK_SIZE_Y || z >= CHUNK_SIZE_Z)
        return;

    blocks[x][y][z] = block;
}

