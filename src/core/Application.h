#pragma once

#include <memory>

// Forward declarations
class Window;
class Renderer;
class Camera;

class Application {
    bool m_running = false;
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Camera> m_camera;
    
public:
    Application();
    ~Application();
    
    void Run();

private:
    void Init();
    void Shutdown();
    void Update(float deltaTime);
    void Render();
};
