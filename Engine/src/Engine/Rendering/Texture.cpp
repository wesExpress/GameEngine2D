#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/TextureOpenGL.h"

#include "Logging.h"
#include "EngineDefines.h"

namespace Engine
{
    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::Get())
        {
        case RendererAPI::API::None:
            ENGINE_ASSERT(0, "No render API is not suppoted!")
                return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<Texture2DOpenGL>(width, height);
        default:
            ENGINE_ASSERT(0, "Unknown render API!");
            return nullptr;
        }
    }

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch(Renderer::Get())
        {
            case RendererAPI::API::None:
                ENGINE_ASSERT(0, "No render API is not suppoted!")
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<Texture2DOpenGL>(path);
            default:
                ENGINE_ASSERT(0, "Unknown render API!");
                return nullptr;
        }
    }
}