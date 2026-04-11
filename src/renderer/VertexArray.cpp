#include "VertexArray.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "BufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <iostream>

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

void VertexArray::AddVertexBuffer(
    const VertexBuffer& vertexBuffer,
    const BufferLayout& layout
) {
    Bind();
    vertexBuffer.Bind();

    glEnableVertexAttribArray(m_vertexBufferIndex);

    glVertexAttribPointer(
        m_vertexBufferIndex,
        layout.size,
        layout.type,
        layout.normalized,
        sizeof(glm::vec3),
        (void*)0
    );
    
    m_vertexBufferIndex++;
}

