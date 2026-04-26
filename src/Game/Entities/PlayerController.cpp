#include "PlayerController.h"

#include <iostream>

#include <glm/glm.hpp>

#include "Entities/Player.h"

namespace Game {
    
void PlayerController::Update(Player& player, const InputState& input, float dt) {
	glm::vec3 position = player.GetEyePosition();
	glm::vec3 forward = player.GetForward();
	glm::vec3 right = player.GetRight();

	// Ignore vertical movement (FPS style)
	forward.y = 0.0f;
	forward = glm::normalize(forward);

	float velocity = player.GetSpeed() * dt;

	if (input.MoveForward)
		position += forward * velocity;
	if (input.MoveBackward)
		position -= forward * velocity;
	if (input.MoveRight)
		position += right * velocity;
	if (input.MoveLeft)
		position -= right * velocity;
    if (input.Jump)
        player.Jump();

	// Mouse rotation
	float yaw = player.GetYaw();
	float pitch = player.GetPitch();

	float sensitivity = 0.1f;

	yaw   += input.MouseDeltaX * sensitivity;
	pitch += input.MouseDeltaY * sensitivity;

	// Clamp pitch
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	player.SetPosition(position);
	player.SetRotation(yaw, pitch);
}

}

