#pragma once

#include <glm/glm.hpp>

namespace ACE {
    
class Camera{
    glm::vec3 Position = {0.0f, 10.0f, 0.0f};
    glm::vec3 Front    = {0.0f, 0.0f, -1.0f};
    glm::vec3 Right    = {1.0f, 0.0f, 0.0f};
    glm::vec3 Up       = {0.0f, 1.0f, 0.0f};

    float FOV = 70.0f;
    float AspectRadio = 16.0f / 9.0f;
    float NearPlane = 0.01f;
    float FarPlane = 1024.0f;

    float Yaw = -90.0f;
    float Pitch = 0.0f;
    float Sensitivity = 0.1f;

    float Speed = 5.0f;
public:
    Camera() = default;
    ~Camera() = default;

    void Update(float deltaTime);

    void SetSpeed(float speed) { Speed = speed; }
    void SetPosition(glm::vec3 position) { Position = position; }
    void SetFront(glm::vec3 front) { Front = front; }
    void SetRight(glm::vec3 right) { Right = right; }
    void SetYaw(float yaw) { Yaw = yaw; }
    void SetPitch(float pitch) { Pitch = pitch; }
    void SetRotation(float yaw, float pitch) { Yaw = yaw; Pitch = pitch; }

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    glm::vec3 GetPosition() { return Position; }

    void MouseMovement(float xoffset, float yoffset);
private:
    void UpdateVectors();
};

}

