#include "RendererCommand.h"
#include "Platform/OpenGL/RendererAPIOpenGL.h"

namespace Engine
{
    RendererAPI* RendererCommand::m_rendererAPI = new RendererAPIOpenGL;
}