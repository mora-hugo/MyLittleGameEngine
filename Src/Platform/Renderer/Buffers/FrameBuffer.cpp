#include "Renderer/Buffers/FrameBuffer.h"
#include "Assertion.h"
HC::FrameBuffer::FrameBuffer(const glm::vec2 &size) {
    Create(size);
}

HC::FrameBuffer::~FrameBuffer() {
    Destroy();
}


void HC::FrameBuffer::Unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void HC::FrameBuffer::Bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
}

void HC::FrameBuffer::Resize(const glm::vec2 &size) {
    Destroy();
    Create(size);
}



void HC::FrameBuffer::Destroy() {
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &colorAttachment);
    glDeleteRenderbuffers(1, &rbo);
}

void HC::FrameBuffer::Create(const glm::vec2 &size) {
    framebufferSize = size;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glGenTextures(1, &colorAttachment);
    glBindTexture(GL_TEXTURE_2D, colorAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    Assertion(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete!");


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
