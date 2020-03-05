#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/ShaderOpenGL.h"

#include "Logging.h"
#include "EngineDefines.h"

namespace Engine
{
    Ref<Shader> Shader::Create(const std::string& filename)
    {
        switch(Renderer::Get())
        {
            case RendererAPI::API::None:
                ENGINE_ASSERT(0, "No render API is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_unique<ShaderOpenGL>(filename);
            default:
                ENGINE_ASSERT(0, "Unknown renderer API!");
                return nullptr;
        }
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragSrc)
    {
        switch(Renderer::Get())
        {
            case RendererAPI::API::None:
                ENGINE_ASSERT(0, "No render API is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_unique<ShaderOpenGL>(name, vertexSrc, fragSrc);
            default:
                ENGINE_ASSERT(0, "Unknown renderer API!");
                return nullptr;
        }
    }

    bool ShaderLibrary::Exists(const std::string& name)
    {
        return m_shaders.find(name) != m_shaders.end();
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {
        ENGINE_ASSERT(!Exists(name), "Shader `{0}' already exists in library!", name);
        m_shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        std::string shaderName = shader->GetName();
        Add(shaderName, shader);
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name)
    {
        auto shader = Shader::Create(name);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        ENGINE_ASSERT(Exists(name), "Shader `{0}' does not exist in library!", name);
        return m_shaders[name];
    }
}
