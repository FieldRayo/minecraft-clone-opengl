#pragma once

#include <cstdint>

#include <glm/glm.hpp>

namespace Game {

struct Hitbox {
    glm::vec3 first;
    glm::vec3 last;
};
    
class Entity {
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;

    Hitbox m_hitbox; // Relative points

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_velocity = { 0.0f, 0.0f, 0.0f };
    float m_speed = 5.0f;
    float m_gravity = 0.5f;
    float m_jumpForce = 0.125f;

    bool IsOnGround=false;
public:
    uint32_t m_uuid;
    Entity();
    Entity(glm::vec3 position);
    ~Entity();

    virtual void Update(float dt);
    virtual void Jump();

    virtual void SetSpeed(float speed) { m_speed = speed; }
    virtual void SetPosition(glm::vec3 position) { m_position = position; };
    virtual void SetYaw(float yaw) { m_yaw = yaw; }
    virtual void SetPitch(float pitch) { m_pitch = pitch; }
    virtual void SetRotation(float yaw, float pitch) { m_yaw = yaw; m_pitch = pitch; }
    virtual void SetVelocity(glm::vec3 velocity) { m_velocity = velocity; }

    virtual float GetSpeed() const { return m_speed; };
    virtual glm::vec3 GetEyePosition() const { return m_position; }
    virtual glm::vec3 GetFeetPosition() { return { m_position.x, m_position.y + m_hitbox.last.y, m_position.z }; };
    virtual float GetYaw()  const { return m_yaw; }
    virtual float GetPitch() const { return m_pitch; }
    virtual glm::vec3 GetVelocity() const { return m_velocity; }
    virtual glm::vec3 GetForward() const;
    virtual glm::vec3 GetRight() const;
};

}

// Seguire utilizando glm porque no depende de la API de graficos
// En proyectos serios se intenta reducir dependencias entonces en
// ese caso si se utilizaria una vercion optimizada de una libreria
// de matrices
