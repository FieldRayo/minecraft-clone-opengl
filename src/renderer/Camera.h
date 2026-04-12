#pragma once

#include <glm/glm.hpp>

class Camera{
    glm::vec3 Position = {0.0f, 0.0f, 0.0f};
    float Speed = 5.0f;
public:
    Camera() = default;
    ~Camera() = default;

    void Update(float deltaTime);
};
