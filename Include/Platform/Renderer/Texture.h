#pragma once

#include <vector>
#include <glad/glad.h>
#include <stb_image/stb_image.h>

namespace HC {
    class Texture {
    public:
        Texture(const std::vector<uint8_t>& textureData);
        ~Texture();

        void CreateTexture();
        [[nodiscard]] unsigned int GetTextureID() const { return textureID; }
        void Bind();

        int GetWidth() const { return width; }
        int GetHeight() const { return height; }
        int GetChannels() const { return channels; }
        int GetFormat() const { return format; }
    private:
        stbi_uc* data;
        int width, height, channels, format = 0;

        GLuint textureID;


    };
}