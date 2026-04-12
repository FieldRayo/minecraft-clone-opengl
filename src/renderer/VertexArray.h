#pragma once

#include <memory>
#include <vector>

#include "BufferLayout.h"

class VertexBuffer;
class IndexBuffer;
class BufferLayout;

unsigned int ShaderDataTypeToGLType(ShaderDataType type);

class VertexArray{
    unsigned int ID = 0;

    std::vector<VertexBuffer> m_vertexBuffers;
    std::unique_ptr<IndexBuffer> m_indexBuffer;

    unsigned int m_vertexBufferIndex = 0;
public:
    VertexArray();
    ~VertexArray();

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    VertexArray(VertexArray&& other) noexcept;
    VertexArray& operator=(VertexArray&& other) noexcept;

    void Bind() const;
    void UnBind() const;

    void AddVertexBuffer(const VertexBuffer& vertexBuffer, const BufferLayout& layout);
    void SetIndexBuffer(std::unique_ptr<IndexBuffer>& indexBuffer);

    const std::vector<VertexBuffer>& GetVertexBuffers() const { return m_vertexBuffers; }
    const std::unique_ptr<IndexBuffer>& GetIndexBuffer() const { return m_indexBuffer; }
};
