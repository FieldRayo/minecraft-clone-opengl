#pragma once

#include <cmath>
#include <cstdint>

#include <glm/glm.hpp>

#include "Chunk.h"

// Fractal Noise Parameters
constexpr int octaves       = 5;
constexpr float persistence = 0.3f;
constexpr float lacunarity  = 1.8f;
constexpr float amp         = 1.0f;
constexpr float frec        = 0.001f;

namespace Game {
    
class WorldGen {
    uint32_t Seed;
public:
    WorldGen();
    WorldGen(int32_t seed);
    ~WorldGen();
    
    Chunk ChunkGenerate(glm::ivec2 position);
};

}
