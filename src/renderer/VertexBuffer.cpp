#include "VertexBuffer.h"

#include <glad/glad.h>
#include <iostream>

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &ID);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &ID);
}

VertexBuffer::VertexBuffer(const void* data, uint32_t size) {
    glGenBuffers(1, &ID);
    SetData(data, size);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept {
    ID = other.ID;
    const void* data = other.GetData();
    SetData(data, sizeof(data));
    other.ID = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept {
    if (this != &other) {
        glDeleteBuffers(1, &ID);

        ID = other.ID;
        const void* data = other.GetData();
        SetData(data, sizeof(data));

        other.ID = 0;
    }
    return *this;
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::UnBind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, uint32_t size) {
    Bind();
    glBufferData(
        GL_ARRAY_BUFFER,
        size,
        data,
        GL_STATIC_DRAW
    );

    Data = data;
}

