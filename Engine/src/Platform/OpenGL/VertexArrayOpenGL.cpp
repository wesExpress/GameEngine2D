#include "VertexArrayOpenGL.h"

#include <glad/glad.h>

namespace Engine
{
    VertexArrayOpenGL::VertexArrayOpenGL()
    {
        glGenVertexArrays(1, &m_rendererID);
        glBindVertexArray(m_rendererID);
    }

    VertexArrayOpenGL::~VertexArrayOpenGL()
    {
        glDeleteVertexArrays(1, &m_rendererID);
    }

    void VertexArrayOpenGL::Bind() const
    {
        glBindVertexArray(m_rendererID);
    }

    void VertexArrayOpenGL::UnBind() const
    {
        glBindVertexArray(0);
    }
}