#pragma once

#include <cstdint>

class IndexBuffer {
    unsigned int ID;
public:
    IndexBuffer();
    ~IndexBuffer();

    IndexBuffer(const uint32_t* indices, uint32_t count);

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    IndexBuffer(IndexBuffer&& other) noexcept;
    IndexBuffer& operator=(IndexBuffer&& other) noexcept;

    void Bind() const;
    void UnBind() const;

    void SetData(const uint32_t* indices, uint32_t count);
};
