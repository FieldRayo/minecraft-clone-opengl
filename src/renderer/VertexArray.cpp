#include "VertexArray.h"

#include <iostream>
#include <cstdint>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "core/Assert.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

unsigned int ShaderDataTypeToGLType(ShaderDataType type) {
    switch(type) {
        case ShaderDataType::Float  : return GL_FLOAT;
        case ShaderDataType::Float2 : return GL_FLOAT;
        case ShaderDataType::Float3 : return GL_FLOAT;
        case ShaderDataType::Float4 : return GL_FLOAT;

        case ShaderDataType::Int  : return GL_INT;
        case ShaderDataType::Int2 : return GL_INT;
        case ShaderDataType::Int3 : return GL_INT;
        case ShaderDataType::Int4 : return GL_INT;

        case ShaderDataType::Mat3 : return GL_FLOAT;
        case ShaderDataType::Mat4 : return GL_FLOAT;

        case ShaderDataType::Bool : return GL_BOOL;
    }

    ACE_ASSERT(false, "Unkow ShaderDataType!");

    return 0;
}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &ID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &ID);
}

void VertexArray::Bind() const {
    glBindVertexArray(ID);
}

void VertexArray::UnBind() const {
    glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(std::unique_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout) {
    Bind();
    vertexBuffer->Bind();
    
    for(auto& element : layout.GetElements()) {
        glEnableVertexAttribArray(m_vertexBufferIndex);

        uint32_t size = element.GetComponentCount();
        unsigned int type = ShaderDataTypeToGLType(element.Type);
        bool normalized = element.Normalized;
        uint32_t stride = layout.GetStride();
        uint32_t offset = element.Offset;

        glVertexAttribPointer(
            m_vertexBufferIndex,
            size,
            type,
            normalized,
            stride,
            (const void*)(uintptr_t)offset
        );
        
        m_vertexBufferIndex++;
    }
}

void VertexArray::SetIndexBuffer(std::unique_ptr<IndexBuffer>& indexBuffer) {
    Bind();
    indexBuffer->Bind();
    m_indexBuffer = std::move(indexBuffer);
}

