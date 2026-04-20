#pragma once

#include <cmath>
#include <cstdint>

#include <glm/glm.hpp>

#include "Chunk.h"
#include "Math/PerlinNoise.h"

namespace Game {
    
class WorldGen {
    uint32_t seed;
public:
    WorldGen();
    ~WorldGen();
    
    Chunk ChunkGenerate(glm::ivec2 position);

    static float Perlin(glm::vec2 position);
};

}
