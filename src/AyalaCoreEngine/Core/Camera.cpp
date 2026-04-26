#include "Camera.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Input.h"
#include "Game/Voxel/World.h"

namespace ACE {
    
void Camera::Update(float deltaTime) {
    UpdateVectors();
}

void Camera::MouseMovement(float xoffset, float yoffset) {
    //xoffset *= Sensitivity;
    //yoffset *= Sensitivity;

    //Yaw   += xoffset;
    //Pitch += yoffset;

    if (Pitch > 89.0f) Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;

    UpdateVectors();
}

void Camera::UpdateVectors() {
    glm::vec3 front;

    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    Front = glm::normalize(front);
    Right = normalize(cross(Front, Up));
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(
        Position,
        Position + Front,
        Up
    );
}

glm::mat4 Camera::GetProjectionMatrix() const {
    return glm::perspective(
        glm::radians(FOV),
        AspectRadio,
        NearPlane,
        FarPlane
    );
}

}

