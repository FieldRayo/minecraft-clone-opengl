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
#include "voxel/ChunkMesh.h"
#include "voxel/Chunk.h"
#include "renderer/Texture.h"

double mousePosX, mousePosY;

Application::Application() {
    Init();
}

Application::~Application() = default;

std::unique_ptr<ChunkMesh> chunkMesh;
std::unique_ptr<ChunkMesh> chunkMesh2;
Chunk chunk;
Chunk chunk2({ 16.0f, 0.0f, 0.0f });

void Application::Run() {
    // Fill Chunk
    for (uint32_t x = 0; x < CHUNK_SIZE_X; ++x) 
    for (uint32_t y = 0; y < CHUNK_SIZE_Y; ++y)
    for (uint32_t z = 0; z < CHUNK_SIZE_Z; ++z) {
        if (y == CHUNK_SIZE_Y - 1)
            chunk.SetBlock(Block(1, BlockType::Grass), x, y, z);  // capa top
        else if (y >= CHUNK_SIZE_Y - 4)
            chunk.SetBlock(Block(1, BlockType::Dirt), x, y, z);   // capas de dirt
        else
            chunk.SetBlock(Block(1, BlockType::Stone), x, y, z);  // resto stone
    }
    // Fill Chunk 2
    for (uint32_t x = 0; x < CHUNK_SIZE_X; ++x) 
    for (uint32_t y = 0; y < CHUNK_SIZE_Y; ++y)
    for (uint32_t z = 0; z < CHUNK_SIZE_Z; ++z) {
        if (1)
            chunk2.SetBlock(Block(1, BlockType::Grass), x, y, z);
        else
            chunk2.SetBlock(Block(1, BlockType::Air), x, y, z);
    }

    ChunkContext chunkContext(chunk);
    ChunkContext chunkContext2(chunk2);
    chunkContext.Right = &chunk2;
    chunkContext2.Left = &chunk;

    chunkMesh = std::make_unique<ChunkMesh>(chunkContext);
    chunkMesh->Build();

    chunkMesh2 = std::make_unique<ChunkMesh>(chunkContext2);
    chunkMesh2->Build();

    float lastTime = 0;
    while (m_running && m_window->isOpen()) {
        float currentTime = glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        Render();
        Update(dt);

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

int p=0;
void Application::Update(float deltaTime) {
    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
        m_running = false;
    if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
        m_camera->SetSpeed(20.0f);
    else
        m_camera->SetSpeed(10.0f);
    if (Input::IsKeyPressed(GLFW_KEY_U)) {
        chunk.SetBlock(Block(1, BlockType::Air), 0, p, 0);

        chunkMesh->Update();
        chunkMesh2->Update();
        p++;
    }
        
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
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_renderer->GetShader()->use();
    m_renderer->GetShader()->setVec3("uCol", { 1.0f, 0.0f, 0.0f });
    Mesh mesh;
    mesh.Upload(chunkMesh->GetVertices(), chunkMesh->GetIndices());
    m_renderer->Draw(mesh, *m_camera);

    m_renderer->GetShader()->setVec3("uCol", { 0.0f, 1.0f, 0.0f });
    Mesh mesh2;
    mesh2.Upload(chunkMesh2->GetVertices(), chunkMesh2->GetIndices());
    m_renderer->Draw(mesh2, *m_camera);
}

