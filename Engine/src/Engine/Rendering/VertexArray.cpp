#include "VertexArray.h"
#include "RenderAPI.h"
#include "Platform/OpenGL/VertexArrayOpenGL.h"

#include "Logging.h"

namespace Engine
{
    VertexArray* VertexArray::Create()
    {
        switch(Renderer::Get())
        {
            case RenderAPI::None:
                ENGINE_ERROR("No render API is no suppoted!");
                return nullptr;
            case RenderAPI::OpenGL:
                return new VertexArrayOpenGL();
            default:
                ENGINE_ERROR("Unknown render API!");
                return nullptr;
        }
    }
}

#include "Logging.h"