#include "BufferOpenGL.h"
#include "Logging.h"

#include <glad/glad.h>

namespace Engine
{
    VertexBufferOpenGL::VertexBufferOpenGL(float* vertices, uint32_t size)
    {
        glGenBuffers(1, &m_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

        ENGINE_INFO("Created OpenGL Vertex Buffer.");
    }

    VertexBufferOpenGL::~VertexBufferOpenGL()
    {
        glDeleteBuffers(1, &m_rendererID);
    }

    void VertexBufferOpenGL::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    }

    void VertexBufferOpenGL::UnBind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    IndexBufferOpenGL::IndexBufferOpenGL(uint32_t* indices, uint32_t count)
    :
    m_count(count)
    {
        glGenBuffers(1, &m_rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

        ENGINE_INFO("Created OpenGL Index Buffer.");
    }

    IndexBufferOpenGL::~IndexBufferOpenGL()
    {
        glDeleteBuffers(1, &m_rendererID);
    }

    void IndexBufferOpenGL::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    }

    void IndexBufferOpenGL::UnBind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}