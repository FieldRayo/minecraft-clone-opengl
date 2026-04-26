#include "Random.h"

std::mt19937 Random::s_rng(std::random_device{}());

void Random::Init(uint32_t seed) {
    std::mt19937 s_rng(seed);   
}

int32_t Random::Int32() {
    std::uniform_int_distribution<int32_t> intDist(INT32_MIN + 1, INT32_MAX);
    return intDist(s_rng);
}

int32_t Random::Int32(int32_t min, int32_t max) {
    std::uniform_int_distribution<int32_t> intDist(min, max);
    return intDist(s_rng);
}

uint32_t Random::UInt32() {
    return s_rng();
}

uint32_t Random::UInt32(uint32_t min, uint32_t max) {
    std::uniform_int_distribution<uint32_t> intDist(min, max);
    return intDist(s_rng);
}

float Random::Float(float min, float max) {
    std::uniform_real_distribution<float> floatDist(min, max);
    return floatDist(s_rng);
}

