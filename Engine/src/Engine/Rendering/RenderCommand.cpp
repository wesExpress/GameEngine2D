#include "RenderCommand.h"
#include "Platform/OpenGL/RendererAPIOpenGL.h"

namespace Engine
{
    RendererAPI* RenderCommand::m_rendererAPI = new RendererAPIOpenGL;
}