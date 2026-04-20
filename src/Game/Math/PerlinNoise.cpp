#include "PerlinNoise.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>

int32_t PerlinNoise::Seed = 0xFFFFFFFF;
std::array<int, 512> PerlinNoise::P = {};

// Tabla de permutación original de Ken Perlin (256 valores)
static constexpr int PERM_TABLE[256] = {
    151,160,137, 91, 90, 15,131, 13,201, 95, 96, 53,194,233,  7,225,
    140, 36,103, 30, 69,142,  8, 99, 37,240, 21, 10, 23,190,  6,148,
    247,120,234, 75,  0, 26,197, 62, 94,252,219,203,117, 35, 11, 32,
     57,177, 33, 88,237,149, 56, 87,174, 20,125,136,171,168, 68,175,
     74,165, 71,134,139, 48, 27,166, 77,146,158,231, 83,111,229,122,
     60,211,133,230,220,105, 92, 41, 55, 46,245, 40,244,102,143, 54,
     65, 25, 63,161,  1,216, 80, 73,209, 76,132,187,208, 89, 18,169,
    200,196,135,130,116,188,159, 86,164,100,109,198,173,186,  3, 64,
     52,217,226,250,124,123,  5,202, 38,147,118,126,255, 82, 85,212,
    207,206, 59,227, 47, 16, 58, 17,182,189, 28, 42,223,183,170,213,
    119,248,152,  2, 44,154,163, 70,221,153,101,155,167, 43,172,  9,
    129, 22, 39,253, 19, 98,108,110, 79,113,224,232,178,185,112,104,
    218,246, 97,228,251, 34,242,193,238,210,144, 12,191,179,162,241,
     81, 51,145,235,249, 14,239,107, 49,192,214, 31,181,199,106,157,
    184, 84,204,176,115,121, 50, 45,127,  4,150,254,138,236,205, 93,
    222,114, 67, 29, 24, 72,243,141,128,195, 78, 66,215, 61,156,180
};

void PerlinNoise::InitPermutation() {
    if (Seed == 0xFFFFFFFF) {
        for (int i = 0; i < 256; i++)
            P[i] = P[i + 256] = PERM_TABLE[i];
    } else {
        std::array<int, 256> p;
        std::iota(p.begin(), p.end(), 0);
        std::shuffle(p.begin(), p.end(), std::default_random_engine(Seed));
        for (int i = 0; i < 256; i++)
            P[i] = P[i + 256] = p[i];
    }
}

// Gradientes unitarios — 8 direcciones diagonales
glm::vec2 PerlinNoise::Gradient(int hash) {
    switch (hash & 7) {
        case 0: return { 1, 0};
        case 1: return {-1, 0};
        case 2: return { 0, 1};
        case 3: return { 0,-1};
        case 4: return { 0.7071f,  0.7071f};
        case 5: return {-0.7071f,  0.7071f};
        case 6: return { 0.7071f, -0.7071f};
        default:return {-0.7071f, -0.7071f};
    }
}

float PerlinNoise::fade(float t) {
    // Quintica de Perlin — C² continua (mejor que la cubica)
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise::lerp(float a, float b, float t) {
    return a + t * (b - a);
}

float PerlinNoise::GenerateNoise(glm::vec2 position) {
    // Celda entera
    int X = (int)floor(position.x) & 255;
    int Y = (int)floor(position.y) & 255;

    // Posición local dentro de la celda
    float x = position.x - floor(position.x);
    float y = position.y - floor(position.y);

    // Curvas de suavizado
    float u = fade(x);
    float v = fade(y);

    // Hash de las 4 esquinas usando la tabla P
    int aa = P[P[X  ] + Y  ];
    int ab = P[P[X  ] + Y+1];
    int ba = P[P[X+1] + Y  ];
    int bb = P[P[X+1] + Y+1];

    // Dot products con gradiente de cada esquina
    glm::vec2 gAA = Gradient(aa);
    glm::vec2 gBA = Gradient(ba);
    glm::vec2 gAB = Gradient(ab);
    glm::vec2 gBB = Gradient(bb);

    float dotAA = gAA.x * x       + gAA.y * y;
    float dotBA = gBA.x * (x-1)   + gBA.y * y;
    float dotAB = gAB.x * x       + gAB.y * (y-1);
    float dotBB = gBB.x * (x-1)   + gBB.y * (y-1);

    // Interpolación bilineal suavizada
    float i0 = lerp(dotAA, dotBA, u);
    float i1 = lerp(dotAB, dotBB, u);
    float value = lerp(i0, i1, v);

    return glm::clamp(value, -1.0f, 1.0f);
}

float PerlinNoise::FractalNoise(glm::vec2 position, int octaves,
                                float persistence, float lacunarity,
                                float amp, float frec) {
    float total    = 0.0f;
    float amplitude = amp;
    float frequency = frec;
    float maxValue  = 0.0f;

    for (int i = 0; i < octaves; i++) {
        total    += GenerateNoise({position.x * frequency,
                                   position.y * frequency}) * amplitude;
        maxValue += amplitude;
        amplitude *= persistence;
        frequency *= lacunarity;
    }
    return total / maxValue;
}
