#pragma once

enum class BlockType {
    Air,
    Dirt,
    Grass,
    Stone
};

struct BlockTextures {
    const char* Top;
    const char* Bottom;
    const char* Side;
};

inline BlockTextures GetBlockTextures(BlockType type) {
    switch (type) {
        case BlockType::Grass: return {
            "assets/textures/block/grass_block_top.png",
            "assets/textures/block/dirt.png",
            "assets/textures/block/grass_block_side.png"
        };
        case BlockType::Dirt: return {
            "assets/textures/block/dirt.png",
            "assets/textures/block/dirt.png",
            "assets/textures/block/dirt.png"
        };
        case BlockType::Stone: return {
            "assets/textures/block/stone.png",
            "assets/textures/block/stone.png",
            "assets/textures/block/stone.png"
        };
        default: return { nullptr, nullptr, nullptr };
    }
}

class Block {
    uint32_t ID;
    BlockType Type;
public:
    Block() = default;
    ~Block() = default;
    
    Block(uint32_t id, BlockType type) : ID(id), Type(type) {}

    bool IsSolid() const { return Type != BlockType::Air; };
    BlockType GetType() const { return Type; }
};
