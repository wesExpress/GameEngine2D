#include "Shader.h"
#include "RenderAPI.h"
#include "Platform/OpenGL/ShaderOpenGL.h"

#include "Logging.h"

namespace Engine
{
    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragSrc)
    {
        switch(Renderer::Get())
        {
            case RenderAPI::None:
                ENGINE_ERROR("No render API supported!");
                return nullptr;
            case RenderAPI::OpenGL:
                return new ShaderOpenGL(vertexSrc, fragSrc);
            default:
                ENGINE_ERROR("Unknown API!");
                return nullptr;
        }
    }
}