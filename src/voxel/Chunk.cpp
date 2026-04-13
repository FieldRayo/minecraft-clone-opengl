#include "Chunk.h"

Chunk::Chunk() = default;

Chunk::Chunk(glm::vec3 position) : Position(position) { }

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

const glm::vec3& Chunk::GetPosition() const { return Position; }

// --- struct: ChunkContext ---

ChunkContext::ChunkContext(const Chunk& chunk) : Center(chunk) {

}

ChunkContext::~ChunkContext() {

}

