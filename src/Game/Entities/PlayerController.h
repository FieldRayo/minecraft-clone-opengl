#pragma once

#include <AyalaCoreEngine/Core/Input.h>

namespace Game {
    
class Player;

struct InputState {
    bool MoveForward;
    bool MoveBackward;
    bool MoveRight;
    bool MoveLeft;
    bool Jump;
    float MousePosX;
    float MousePosY;
    float MouseDeltaX;
    float MouseDeltaY;
};

class PlayerController {
public:
    void Update(Player& player, const InputState& input, float dt);
};

}

