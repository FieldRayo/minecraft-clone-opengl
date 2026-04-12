#pragma once

class IndexBuffer {
    unsigned int ID;
public:
    IndexBuffer();
    ~IndexBuffer();

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    IndexBuffer(const IndexBuffer&& other);
    IndexBuffer& operator=(const IndexBuffer&& other);

    void Bind();
    void UnBind();
};
