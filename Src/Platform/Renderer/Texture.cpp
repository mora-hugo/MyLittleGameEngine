#include "Renderer/Texture.h"

HC::Texture::Texture(const std::vector<uint8_t> &textureData) {
    data = stbi_load_from_memory(textureData.data(), textureData.size(), &width, &height, &channels, 0);
    format = channels == 3 ? GL_RGB : GL_RGBA;
    CreateTexture();
}

HC::Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

void HC::Texture::CreateTexture() {
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    /* set the texture wrapping/filtering options (on the currently bound texture object) */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, channels == 4 ? GL_RGBA :  GL_RGB, width, height, 0, channels == 4 ? GL_RGBA :  GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);
}

void HC::Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, textureID);
}
