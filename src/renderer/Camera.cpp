#include "Camera.h"

void Camera::Update(float deltaTime) {
    if (Input::IsKeyPressed(GLFW_KEY_W))
        Position.z -= Speed * dt;

    if (Input::IsKeyPressed(GLFW_KEY_S))
        Position.z += Speed * dt;

    if (Input::IsKeyPressed(GLFW_KEY_A))
        Position.x -= Speed * dt;

    if (Input::IsKeyPressed(GLFW_KEY_D))
        Position.x += Speed * dt;
}
