#pragma once

#include <random>
#include <cstdint>

class Random {
    static std::mt19937 s_rng;
public:
    static void Init(uint32_t seed = std::random_device{}());

    static int32_t Int32();
    static int32_t Int32(int32_t min, int32_t max);
    
    static uint32_t UInt32();
    static uint32_t UInt32(uint32_t min, uint32_t max);

    static float Float(float min, float max);
};
