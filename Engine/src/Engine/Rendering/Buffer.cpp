#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/BufferOpenGL.h"

#include "Logging.h"
#include "EngineDefines.h"

namespace Engine
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch(Renderer::Get())
        {
            case RendererAPI::API::None:
                ENGINE_ASSERT(0, "No renderer API is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new VertexBufferOpenGL(vertices, size);
            default:
                ENGINE_ASSERT(0, "Unsupported/unknown render API!");
                return nullptr;
        }
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch(Renderer::Get())
        {
            case RendererAPI::API::None:
                ENGINE_ASSERT(0, "No renderer API is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new IndexBufferOpenGL(indices, count);
            default:
                ENGINE_ASSERT(0, "Unsupported/unknown render API!");
                return nullptr;
        }
    }
}