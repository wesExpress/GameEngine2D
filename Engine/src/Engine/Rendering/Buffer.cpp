#include "Buffer.h"
#include "RenderAPI.h"
#include "Platform/OpenGL/BufferOpenGL.h"

#include "Logging.h"

namespace Engine
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch(Renderer::Get())
        {
            case RenderAPI::None:
                ENGINE_ERROR("No renderer API is not supported!");
                return nullptr;
            case RenderAPI::OpenGL:
                return new VertexBufferOpenGL(vertices, size);
            default:
                ENGINE_ERROR("Unsupported/unknown render API!");
                return nullptr;
        }
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch(Renderer::Get())
        {
            case None:
                ENGINE_ERROR("No renderer API is not supported!");
                return nullptr;
            case OpenGL:
                return new IndexBufferOpenGL(indices, count);
            default:
                ENGINE_ERROR("Unsupported/unknown render API!");
                return nullptr;
        }
    }
}