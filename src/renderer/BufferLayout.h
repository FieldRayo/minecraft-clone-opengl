#pragma once

#include <cstdint>
#include <string>
#include <initializer_list>
#include <vector>

#include <glm/glm.hpp>

#include "core/Assert.h"

enum class ShaderDataType {
    None = 0,
    Float, Float2, Float3, Float4,
    Int,   Int2,   Int3,   Int4,
    Mat3,  Mat4,
    Bool
};

uint32_t ShaderDataTypeSize(ShaderDataType type);

template<typename T> constexpr ShaderDataType GetShaderDataType();

template<> constexpr ShaderDataType GetShaderDataType<float>()     { return ShaderDataType::Float; }
template<> constexpr ShaderDataType GetShaderDataType<glm::vec2>() { return ShaderDataType::Float2; }
template<> constexpr ShaderDataType GetShaderDataType<glm::vec3>() { return ShaderDataType::Float3; }
template<> constexpr ShaderDataType GetShaderDataType<glm::vec4>() { return ShaderDataType::Float4; }

template<> constexpr ShaderDataType GetShaderDataType<int>()        { return ShaderDataType::Int; }
template<> constexpr ShaderDataType GetShaderDataType<glm::ivec2>() { return ShaderDataType::Int2; }
template<> constexpr ShaderDataType GetShaderDataType<glm::ivec3>() { return ShaderDataType::Int3; }
template<> constexpr ShaderDataType GetShaderDataType<glm::ivec4>() { return ShaderDataType::Int4; }

template<> constexpr ShaderDataType GetShaderDataType<glm::mat3>() { return ShaderDataType::Mat3; }
template<> constexpr ShaderDataType GetShaderDataType<glm::mat4>() { return ShaderDataType::Mat4; }

template<> constexpr ShaderDataType GetShaderDataType<bool>() { return ShaderDataType::Bool; }

struct BufferElement{
    std::string Name;
    ShaderDataType Type;
    uint32_t Size;
    size_t Offset;
    bool Normalized;

    BufferElement() = default;
    BufferElement(const std::string& name, ShaderDataType type, bool normalized=false);

    uint32_t GetComponentCount() const;
};

class BufferLayout {
    std::vector<BufferElement> m_elements;
    uint32_t m_stride = 0;
public:
    BufferLayout() = default;
    ~BufferLayout() = default;

    BufferLayout(std::initializer_list<BufferElement> elements);

    const std::vector<BufferElement>& GetElements() const { return m_elements; }
    uint32_t GetStride() const { return m_stride; }

    template <typename T>
    void Push(const std::string& name) { m_elements.emplace_back(name, GetShaderDataType<T>(), false); CalculateOffsetsAndStride(); }
    
    std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
private:
    void CalculateOffsetsAndStride();
};
