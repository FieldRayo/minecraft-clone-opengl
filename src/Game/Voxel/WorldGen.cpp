#include "WorldGen.h"

#include "Math/PerlinNoise.h"

namespace Game {

WorldGen::WorldGen() {
    PerlinNoise::InitPermutation();
}

WorldGen::WorldGen(int32_t seed) {
    Seed = seed;
    PerlinNoise::SetSeed(Seed);
    PerlinNoise::InitPermutation();
}

WorldGen::~WorldGen() = default;

Chunk WorldGen::ChunkGenerate(glm::ivec2 position) {
    Chunk chunk(position);

    for (uint32_t x = 0; x < CHUNK_SIZE_X; ++x)
    for (uint32_t z = 0; z < CHUNK_SIZE_Z; ++z) {

        float worldX = ((int)x + position.x) * (int)CHUNK_SIZE_X;
        float worldZ = ((int)z + position.y) * (int)CHUNK_SIZE_Z;

        float noise = PerlinNoise::FractalNoise(
            { worldX, worldZ },
            octaves, persistence, lacunarity, amp, frec 
        );
        noise = (noise + 1.0f) * 0.5f;

        int height = (int)(noise * CHUNK_SIZE_Y);
        height = glm::clamp(height, 1, (int)CHUNK_SIZE_Y - 1);
        

        for(uint32_t y = 0; y < height; ++y)
            chunk.SetBlock(Block(1, BlockType::Grass), x, y, z);
        
    }

    return chunk;
}

}
