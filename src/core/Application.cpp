#include "Application.h"

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Window.h"
#include "Input.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/BufferLayout.h"
#include "renderer/IndexBuffer.h"
#include "voxel/ChunkMesh.h"
#include "voxel/Chunk.h"

Application::Application() {
    Init();
}

Application::~Application() = default;

void Application::Run() {

    Shader shaders({
        { GL_VERTEX_SHADER, "shaders/vertex.glsl" },
        { GL_FRAGMENT_SHADER, "shaders/fragment.glsl" }
    });

    shaders.use();

    Chunk chunk;
    ChunkMesh chunkMesh;
    chunkMesh.Build(chunk);

    const auto& vertices = chunkMesh.GetVertices();
    const auto& indices = chunkMesh.GetIndices();

    auto VBO = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(float));
    auto VAO = std::make_unique<VertexArray>();
    auto IBO = std::make_unique<IndexBuffer>(indices.data(), indices.size());

    BufferLayout layout({
        { "aPos", ShaderDataType::Float3 }
    });

    VAO->AddVertexBuffer(VBO, layout);
    VAO->SetIndexBuffer(IBO);

    Input::Init(m_window->GetHandle());
    while (m_running && m_window->isOpen()) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) {
            Shutdown();
        }

        VAO->Bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        m_window->SwapBuffers();
        m_window->PollEvents();
    }
    
    Shutdown();
}

void Application::Init() {
    m_running = true;
    m_window = std::make_unique<Window>();
    m_window->Init();
}

void Application::Shutdown() {
    m_running = false;
    m_window->RequestClose();
}

void Application::Update(float deltaTime) {}

void Application::Render() {}

