#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/ShaderOpenGL.h"

#include "Logging.h"
#include "EngineDefines.h"

namespace Engine
{
    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragSrc)
    {
        switch(Renderer::Get())
        {
            case RendererAPI::API::None:
                ENGINE_ASSERT(0, "No render API is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new ShaderOpenGL(vertexSrc, fragSrc);
            default:
                ENGINE_ASSERT(0, "Unknown renderer API!");
                return nullptr;
        }
    }
}