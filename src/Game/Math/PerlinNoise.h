// PerlinNoise.h
#pragma once
#include <glm/glm.hpp>
#include <array>

class PerlinNoise {
    static int32_t Seed;
public:
    static void SetSeed(int32_t seed) { Seed = seed; }
    static void InitPermutation();
    static float GenerateNoise(glm::vec2 position);
    static float FractalNoise(glm::vec2 position, int octaves,
                               float persistence, float lacunarity,
                               float amp, float frec);
private:
    static std::array<int, 512> P;

    static glm::vec2 Gradient(int hash);
    static float fade(float t);
    static float lerp(float a, float b, float t);
};
