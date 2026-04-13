#pragma once

enum class BlockType {
    Air,
    Dirt,
    Grass,
};

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
