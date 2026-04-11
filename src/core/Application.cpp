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

    VertexArray VAO;
    VertexBuffer VBO;

    BufferLayout layout;
    layout.size = 3;
    layout.type = GL_FLOAT;
    layout.normalized = false;

    VAO.AddVertexBuffer(VBO, layout);

    std::vector<glm::vec3> positions = {
        { -0.5f, -0.5f, 0.0f },
        { -0.5f,  0.5f, 0.0f },
        { 0.5f,  -0.5f, 0.0f }
    };
    glBufferData(
        GL_ARRAY_BUFFER,
        positions.size() * sizeof(glm::vec3),
        positions.data(),
        GL_STATIC_DRAW
    );

    Input::Init(m_window->GetHandle());
    while (m_running && m_window->isOpen()) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) {
            Shutdown();
        }

        VAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

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

