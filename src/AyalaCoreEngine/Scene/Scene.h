#pragma once

class Scene {
public:
    virtual void Load() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
};
