#include "Application.h"

#include <iostream>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Window.h"
#include "Input.h"
#include "Camera.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include "Game/Voxel/ChunkMesh.h"
#include "Game/Voxel/Chunk.h"
#include "Game/Voxel/World.h"
#include "Game/Voxel/WorldGen.h"

namespace ACE {
    
double mousePosX, mousePosY;

Application::Application() {
    Init();
}

Application::~Application() = default;

std::vector<std::unique_ptr<Game::ChunkMesh>> chunkMesh;

Game::World w;

void Application::Run() {
    w.Build();
    std::unordered_map<int64_t, Chunk>& renderChunks = w.GetRenderChunks();
    Game::WorldGen wg(2357391842);

    for (auto& [_, c] : renderChunks) {
        c = wg.ChunkGenerate(c.GetPosition());

        auto cm = std::make_unique<Game::ChunkMesh>(c);
        chunkMesh.push_back(std::move(cm));
    }

    for (auto& cm : chunkMesh) {
        cm->Build();
    }

    float lastTime = 0;
    while (m_running && m_window->isOpen()) {
        float currentTime = glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        Render();
        Update(dt);

        // ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowSize(ImVec2(0, 0));
        ImGui::Begin("Debug");
        ImGui::Text("FPS: %d", static_cast<int>(1.0f / dt));
        Chunk* ch = Game::World::GetChunk({ m_camera->GetPosition().x, m_camera->GetPosition().z });
        if (ch != nullptr)
            ImGui::Text("Chunk: X: %i Z: %i", ch->GetPosition().x, ch->GetPosition().y);
        else
            ImGui::Text("Chunk: X: NaN Z: NaN");
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

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    auto shader = std::make_unique<Shader>(std::vector<ShaderSource>{
        { GL_VERTEX_SHADER,   "shaders/vertex.glsl" },
        { GL_FRAGMENT_SHADER, "shaders/fragment.glsl" }
    });

    m_renderer->SetShader(std::move(shader));

    // ImGui
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
        m_camera->SetSpeed(100.0f);
    else
        m_camera->SetSpeed(10.0f);

    if (Input::IsKeyPressed(GLFW_KEY_T)) {
        std::unordered_map<int64_t, Chunk>& renderChunks = w.GetRenderChunks();
        
        for (auto& [_, c] : renderChunks) {
            for (uint32_t x = 0; x < CHUNK_SIZE_X; ++x) 
            for (uint32_t y = 0; y < CHUNK_SIZE_Y; ++y)
            for (uint32_t z = 0; z < CHUNK_SIZE_Z; ++z) {
                if (0)
                    c.SetBlock(Block(1, BlockType::Grass), x, y, z);
                else
                    c.SetBlock(Block(0, BlockType::Air), x, y, z);
            }


        }

        for (auto& cm : chunkMesh) {
            cm->Build();
        }

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

    for (auto& cm : chunkMesh) {
        m_renderer->GetShader()->setVec3("uCol", { 1.0f, 1.0f, 1.0f });
        Mesh mesh;
        mesh.Upload(cm->GetVertices(), cm->GetIndices());
        m_renderer->Draw(mesh, *m_camera);
    }
}

}

