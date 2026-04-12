#pragma once

#include <cstdint>

class VertexBuffer {
    unsigned int ID;
    const void* Data;
public:
    VertexBuffer();
    ~VertexBuffer();

    VertexBuffer(const void* data, uint32_t size);

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    VertexBuffer(VertexBuffer&& other) noexcept;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    void Bind() const;
    void UnBind() const;

    void SetData(const void* data, uint32_t size);

    const void* GetData() const { return Data; }
};
