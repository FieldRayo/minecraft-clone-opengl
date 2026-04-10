#include "Application.h"

#include <glad/glad.h>

#include "Window.h"
#include "Input.h"
#include "renderer/Renderer.h"

Application::Application() {
    Init();
}

Application::~Application() = default;

void Application::Run() {

    Input::Init(m_window->GetHandle());
    while (m_running && m_window->isOpen()) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) {
            Shutdown();
        }

        m_window->SwapBuffers();
        m_window->PollEvents();
    }
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

