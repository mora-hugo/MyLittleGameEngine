#pragma once

class IGLBuffer {
public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    [[nodiscard]] virtual GLuint GetId() const = 0;
};