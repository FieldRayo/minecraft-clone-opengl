#pragma once

#include <unordered_map>
#include <cstdint>
#include <memory>

#include <glm/glm.hpp>

#include "Chunk.h"
#include "Block.h"

namespace Game {

enum class DimentionID { Overworld, Nether, End };

struct WorldSettings {
    uint32_t RenderDistance = 8;
    uint32_t MaxHeight = 256;

    int32_t Seed = 27062007;
};

class World {
    static WorldSettings worldSettings;

public:
    static std::unordered_map<int64_t, Chunk> m_renderChunks;

    World();
    World(const WorldSettings& m_settings);
    ~World();

    void Build();
    
    static void SetWorldSettings(const WorldSettings& settings);

    static std::unordered_map<int64_t, Chunk>& GetRenderChunks() { return m_renderChunks; }

    static int64_t GetChunkKey(glm::ivec2 position);
    static Chunk* GetChunk(glm::ivec2 position);
    static const Block* GetBlock(glm::ivec3 position);
};


}
