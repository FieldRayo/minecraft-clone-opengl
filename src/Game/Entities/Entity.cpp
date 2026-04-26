#include "Entity.h"

#include "Math/Random.h"

uint32_t GenUUID() {
    Random::Init();
    return Random::UInt32();
}

namespace Game {

Entity::Entity() {
    m_uuid = GenUUID();

    m_hitbox.first = { 0.75f, 0.0f, 0.75f };
    m_hitbox.last = { -0.75f, -1.8f, -0.75f };
}

Entity::Entity(glm::vec3 position) {
    m_uuid = GenUUID();
    m_position = position;

    m_hitbox.first = { 0.75f, 0.0f, 0.75f };
    m_hitbox.last = { -0.75f, -1.8f, -0.75f };
}

Entity::~Entity() = default;

void Entity::Update(float dt) {
    if (!IsOnGround)
        m_position -= m_velocity.y * dt;
}

void Entity::Jump() {
    if (IsOnGround) {
        m_velocity.y = m_jumpForce;
        IsOnGround = false;
    }
}

glm::vec3 Entity::GetForward() const {
    glm::vec3 front;

	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	return glm::normalize(front);
}

glm::vec3 Entity::GetRight() const {
	glm::vec3 forward = GetForward();
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	return glm::normalize(glm::cross(forward, worldUp));
}

}

