#include "Application.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

double mousePosX, mousePosY;

Application::Application() {
    Init();
}

Application::~Application() = default;

void Application::Run() {
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
    auto IBO = std::make_unique<IndexBuffer>(indices.data(), indices.size());
    auto VAO = std::make_unique<VertexArray>();
  
    BufferLayout layout;
    layout.Push<glm::vec3>("aPos");

    VAO->AddVertexBuffer(std::move(VBO), layout);
    VAO->SetIndexBuffer(std::move(IBO));

    float lastTime = 0;
    while (m_running && m_window->isOpen()) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentTime = glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        Update(dt);
        
        m_renderer->Draw(*VAO, *m_camera);

        // ImGui 👇
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowSize(ImVec2(0, 0));
        ImGui::Begin("Debug");
        ImGui::Text("FPS: %.1f", 1.0f / dt);
        ImGui::Text("Camera: %.1f %.1f %.1f", 
            m_camera->GetPosition().x,
            m_camera->GetPosition().y,
            m_camera->GetPosition().z);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_window->SwapBuffers();
        m_window->PollEvents();
    }
    
    Shutdown();
}

void Application::Init() {
    m_running = true;

    m_window = std::make_unique<Window>();
    m_renderer = std::make_unique<Renderer>();
    m_camera = std::make_unique<Camera>();

    m_window->Init();
    Input::Init(m_window->GetHandle());

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    auto shader = std::make_unique<Shader>(std::vector<ShaderSource>{
        { GL_VERTEX_SHADER,   "shaders/vertex.glsl" },
        { GL_FRAGMENT_SHADER, "shaders/fragment.glsl" }
    });

    m_renderer->SetShader(std::move(shader));

    // ImGui 👇
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_window->GetHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();
}

void Application::Shutdown() {
    if (!m_running) return;

    // ImGui 👇
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    m_running = false;
    m_window->RequestClose();
}

void Application::Update(float deltaTime) {

    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        m_running = false;
    if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        m_camera->SetSpeed(20.0f);
    else
        m_camera->SetSpeed(10.0f);

    mousePosX = Input::GetMouseX();
    mousePosY = Input::GetMouseY();

    static float lastX = 400, lastY = 300;
    static bool firstMouse = true;

    float xoffset = mousePosX - lastX;
    float yoffset = lastY - mousePosY;

    lastX = mousePosX;
    lastY = mousePosY;

    m_camera->MouseMovement(xoffset, yoffset);
    m_camera->Update(deltaTime);
}

void Application::Render() {

    
}

