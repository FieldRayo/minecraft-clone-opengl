#include "IndexBuffer.h"

#include <glad/glad.h>

IndexBuffer::IndexBuffer() {
    glGenBuffers(1, &ID);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &ID);
}

void IndexBuffer::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBuffer::UnBind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
