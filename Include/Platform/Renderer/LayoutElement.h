#pragma once

#include <glad/glad.h>

struct LayoutElement {
    GLint type;
    GLuint count;
    GLboolean normalized;
    GLsizei offset;
};