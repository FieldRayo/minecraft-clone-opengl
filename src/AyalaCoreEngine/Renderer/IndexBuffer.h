#pragma once

#include <cstdint>

namespace ACE {
    
class IndexBuffer {
    unsigned int ID;
    uint32_t Count;
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

    uint32_t GetCount() const { return Count; }

    void SetData(const uint32_t* indices, uint32_t count);
};

}

