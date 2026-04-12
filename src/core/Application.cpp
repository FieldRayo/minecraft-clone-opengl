#include "Application.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Window.h"
#include "Input.h"
#include "Camera.h"
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

    Chunk chunk;
    
    // Fill Chunk
    for (uint32_t x = 0; x < CHUNK_SIZE_X; ++x) 
    for (uint32_t y = 0; y < CHUNK_SIZE_Y; ++y)
    for (uint32_t z = 0; z < CHUNK_SIZE_Z; ++z) {
        if (1)
            chunk.SetBlock(Block(1, BlockType::Grass), x, y, z);
        else
            chunk.SetBlock(Block(1, BlockType::Air), x, y, z);
    }

    chunk.SetBlock(Block(1, BlockType::Air), 15, 15, 15);

    ChunkMesh chunkMesh;
    chunkMesh.Build(chunk);

    const auto& vertices = chunkMesh.GetVertices();
    const auto& indices = chunkMesh.GetIndices();
    auto VBO = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(float));
    auto VAO = std::make_unique<VertexArray>();
    auto IBO = std::make_unique<IndexBuffer>(indices.data(), indices.size());
    
    /*
    float vertices[] = {
        // position          // color
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    auto VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    auto VAO = std::make_unique<VertexArray>();
    auto IBO = std::make_unique<IndexBuffer>(indices, 3);
*/
    BufferLayout layout;
    layout.Push<glm::vec3>("aPos");

    VAO->AddVertexBuffer(VBO, layout);
    VAO->SetIndexBuffer(IBO);

    Camera camera;
    Input::Init(m_window->GetHandle());
    Renderer render;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    float lastTime = 0;
    while (m_running && m_window->isOpen()) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentTime = glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;
        
        double xPos, yPos;
        xPos = Input::GetMouseX();
        yPos = Input::GetMouseY();

        static float lastX = 400, lastY = 300;
        static bool firstMouse = true;

        float xoffset = xPos - lastX;
        float yoffset = lastY - yPos;

        lastX = xPos;
        lastY = yPos;

        camera.MouseMovement(xoffset, yoffset);
        camera.Update(dt);

        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) {
            Shutdown();
        }
        if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
            camera.SetSpeed(20.0f);
        }else {
            camera.SetSpeed(10.0f);
        }
        
        render.Draw(VAO, shaders, camera);

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

void Application::Render_() {}

