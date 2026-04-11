#include "VertexBuffer.h"

#include <glad/glad.h>
#include <iostream>

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &ID);
}

VertexBuffer::~VertexBuffer() {
   glDeleteBuffers(1, &ID);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept {
    ID = other.ID;
    other.ID = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept {
    if (this != &other) {
        glDeleteBuffers(1, &ID);

        ID = other.ID;
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

