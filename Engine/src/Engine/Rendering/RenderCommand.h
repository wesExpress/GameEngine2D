#ifndef __RenderCommand_H__
#define __RenderCommand_H__

#include "RendererAPI.h"

#include "Engine/EngineDefines.h"

namespace Engine
{
    class RenderCommand
    {
        public:
            inline static void Init()
            {
                m_rendererAPI->Init();
            }
        
            inline static void SetClearColor(const glm::vec4& color)
            {
                m_rendererAPI->SetClearColor(color);
            }
            inline static void Clear()
            {
                m_rendererAPI->Clear();
            }
            inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
            {
                m_rendererAPI->DrawIndexed(vertexArray);
            }

            inline static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
            {
                m_rendererAPI->SetViewPort(x, y, width, height);
            }

        private:
            static RendererAPI* m_rendererAPI;
    };
}

#endif
