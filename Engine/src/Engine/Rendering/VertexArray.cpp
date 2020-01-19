#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/VertexArrayOpenGL.h"

#include "Logging.h"
#include "EngineDefines.h"

namespace Engine
{
    VertexArray* VertexArray::Create()
    {
        switch(Renderer::Get())
        {
            case RendererAPI::API::None:
                ENGINE_ASSERT(0, "No render API is not suppoted!")
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new VertexArrayOpenGL();
            default:
                ENGINE_ASSERT(0, "Unknown render API!");
                return nullptr;
        }
    }
}

#include "Logging.h"