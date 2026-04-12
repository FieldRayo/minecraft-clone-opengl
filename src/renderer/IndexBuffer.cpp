#include "IndexBuffer.h"

#include <glad/glad.h>

IndexBuffer::IndexBuffer() {
    glGenBuffers(1, &ID);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &ID);
}

IndexBuffer::IndexBuffer(const uint32_t* indices, uint32_t count) {
    glGenBuffers(1, &ID);
    SetData(indices, count);
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept {
    ID = other.ID;
    other.ID = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept {
    if (this != &other) {
        glDeleteBuffers(1, &ID);

        ID = other.ID;
        other.ID = 0;
    }
    return *this;
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBuffer::UnBind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::SetData(const uint32_t* indices, uint32_t count) {
    Bind();
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        count*sizeof(uint32_t),
        indices,
        GL_STATIC_DRAW
    );
}

