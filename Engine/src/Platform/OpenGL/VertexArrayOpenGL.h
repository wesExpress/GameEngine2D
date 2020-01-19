#ifndef __VERTEXARRAYOPENGL_H__
#define __VERTEXARRAYOPENGL_H__

#include "Rendering/VertexArray.h"

namespace Engine
{
    class VertexArrayOpenGL : public VertexArray
    {
        public:
            VertexArrayOpenGL();
            virtual ~VertexArrayOpenGL();

            virtual void Bind() const override;
            virtual void UnBind() const override;

            virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
            virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

            inline const virtual std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const override { return m_vertexBuffers; }
            inline const virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const override { return m_indexBuffer; }

        private:
            std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
            std::shared_ptr<IndexBuffer> m_indexBuffer;

            uint32_t m_rendererID;
    };
}

#endif