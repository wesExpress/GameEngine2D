#ifndef __RENDERERAPI_H__
#define __RENDERERAPI_H__

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Engine
{
    class RendererAPI
    {
        public:
            enum API
            {
                None = 0,
                OpenGL
            };
        public:
            virtual void SetClearColor(const glm::vec4& color) = 0;
            virtual void Clear() = 0;  
            virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

            inline static API GetAPI() { return m_api; }
        private:
            static API m_api;
    };
}

#endif