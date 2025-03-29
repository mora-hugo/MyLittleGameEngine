#pragma once

#include "glad/glad.h"

class IGLBuffer {
public:
    virtual ~IGLBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    [[nodiscard]] virtual GLuint GetId() const = 0;

};