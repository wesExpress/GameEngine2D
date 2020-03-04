#include "VertexArrayOpenGL.h"

#include <glad/glad.h>

namespace Engine
{
    static GLenum ShaderTypeToOpenGLType(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:   return GL_INT;

            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4: return GL_FLOAT;

            case ShaderDataType::Bool:   return GL_BOOL;

            default: return 0;
        }
    }

    VertexArrayOpenGL::VertexArrayOpenGL()
    {
        glGenVertexArrays(1, &m_rendererID);
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

    void VertexArrayOpenGL::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        glBindVertexArray(m_rendererID);
        vertexBuffer->Bind();

        const auto& layout = vertexBuffer->GetLayout();
        uint32_t index = 0;

        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index, 
                element.GetElementCount(), 
                ShaderTypeToOpenGLType(element.type), 
                element.normalized ? GL_TRUE : GL_FALSE, 
                layout.GetStride(), 
                ((char*)NULL + element.offset));
            index++;
        }
        m_vertexBuffers.push_back(vertexBuffer);
    }

    void VertexArrayOpenGL::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_rendererID);
        indexBuffer->Bind();

        m_indexBuffer = indexBuffer;
    }
}