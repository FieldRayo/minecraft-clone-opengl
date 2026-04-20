#pragma once

#include <cstdint>

#include <glm/glm.hpp>

class Entity {
    uint32_t m_id;
    
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_velocity;
    float m_speed;
    float m_jumpForce;

    bool IsOnGround;
public:
    Entity();
    Entity(glm::vec3 position);
    ~Entity() = default;

    void SetPosition(glm::vec3 position);

    glm::vec3 GetPosition() const;
};

// Seguire utilizando glm porque no depende de la API de graficos
// En proyectos serios se intenta reducir dependencias entonces en
// ese caso si se utilizaria una vercion optimizada de una libreria
// de matrices
