#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

#include "core/Assert.h"

namespace ACE {
    
Texture::Texture() {
    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1, IDs.data());
}

Texture::Texture(const std::initializer_list<std::string>& paths) {
    stbi_set_flip_vertically_on_load(true);

    IDs.resize(paths.size());
    glGenTextures(IDs.size(), IDs.data());

    Load(paths);
}

Texture::~Texture() {
    glDeleteTextures(IDs.size(), IDs.data());
}

void Texture::Bind(unsigned int id) const {
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::UnBind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Active() const {
    for (uint32_t i=0; i<m_Textures; ++i){
        glActiveTexture(GL_TEXTURE0 + i);  
        Bind(IDs[i]);
    }
}

void Texture::Load(const std::initializer_list<std::string>& paths) {
    uint32_t i = 0;
    for(const auto& path : paths) {
        Bind(IDs[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_NrChannels, 0);
        if (data) {
            GLenum format;
            if (m_NrChannels == 4)      format = GL_RGBA;
            else if (m_NrChannels == 3) format = GL_RGB;
            else                        format = GL_RED;

            glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);

            if (m_NrChannels == 1) {
                GLint swizzle[] = { GL_RED, GL_RED, GL_RED, GL_ONE };
                glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzle);
            }

            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
            i++;
            continue;
        }

        ACE_ASSERT(false, "Failed to load texture!");
    }
    m_Textures = i;
}

}

