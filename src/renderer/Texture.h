#pragma once

#include <string>
#include <cstdint>
#include <vector>

class Texture {
    std::vector<unsigned int> IDs;
    int32_t m_Textures = 0;

    int32_t m_Width;
    int32_t m_Height;
    int32_t m_NrChannels;
public:
    Texture();
    Texture(const std::initializer_list<std::string>& path);
    ~Texture();

    void Bind(unsigned int id) const;
    void UnBind() const;
    void Active() const;
    void Load(const std::initializer_list<std::string>& path);
};
