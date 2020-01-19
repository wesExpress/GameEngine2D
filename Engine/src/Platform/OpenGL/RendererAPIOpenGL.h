#ifndef __RENAPIOPENGL_H__
#define __RENAPIOPENGL_H__

#include "Rendering/RendererAPI.h"

namespace Engine
{
    class RendererAPIOpenGL : public RendererAPI
    {
        public:
            virtual void SetClearColor(const glm::vec4& color) override;
            virtual void Clear() override;
            virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexBuffer) override;
    };
}

#endif