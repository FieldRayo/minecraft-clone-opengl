#include "BufferLayout.h"

#include <iostream>

uint32_t ShaderDataTypeSize(ShaderDataType type) {
    switch (type) {
        case ShaderDataType::Float  : return 4;
        case ShaderDataType::Float2 : return 4 * 2;
        case ShaderDataType::Float3 : return 4 * 3;
        case ShaderDataType::Float4 : return 4 * 4;

        case ShaderDataType::Int  : return 4;
        case ShaderDataType::Int2 : return 4 * 2;
        case ShaderDataType::Int3 : return 4 * 3;
        case ShaderDataType::Int4 : return 4 * 4;

        case ShaderDataType::Mat3 : return 4 * 3 * 3;
        case ShaderDataType::Mat4 : return 4 * 4 * 4;

        case ShaderDataType::Bool : return 1;
    }

    ACE_ASSERT(false, "Unknow ShaderDataType!");

    return 0;
}

// --- struct: BufferElement ---

BufferElement::BufferElement(const std::string& name, ShaderDataType type, bool normalized) : 
    Name(name),
    Type(type),
    Normalized(normalized)
{ }

uint32_t BufferElement::GetComponentCount() const {
    switch (Type) {
        case ShaderDataType::Float  : return 1;
        case ShaderDataType::Float2 : return 2;
        case ShaderDataType::Float3 : return 3;
        case ShaderDataType::Float4 : return 4;

        case ShaderDataType::Int  : return 1;
        case ShaderDataType::Int2 : return 2;
        case ShaderDataType::Int3 : return 3;
        case ShaderDataType::Int4 : return 4;

        case ShaderDataType::Mat3 : return 3;
        case ShaderDataType::Mat4 : return 4;

        case ShaderDataType::Bool : return 1;
    }

    ACE_ASSERT(false, "Unknow ShaderDataType!");

    return 0;
}

// --- class: BufferLayout ---

BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements) : 
    m_elements(elements) 
{
    CalculateOffsetsAndStride();
}

void BufferLayout::CalculateOffsetsAndStride() {
    size_t offset = 0;
    m_stride = 0;
    for (auto& element : m_elements) {
        element.Offset = offset;
        uint32_t size = ShaderDataTypeSize(element.Type);
        element.Size = size;
        offset += size;
        m_stride += size;
    }
}

