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

            virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
            virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

            inline const virtual std::vector<Ref<VertexBuffer>> GetVertexBuffers() const override { return m_vertexBuffers; }
            inline const virtual Ref<IndexBuffer> GetIndexBuffer() const override { return m_indexBuffer; }

        private:
            std::vector<Ref<VertexBuffer>> m_vertexBuffers;
            Ref<IndexBuffer> m_indexBuffer;

            uint32_t m_rendererID;
    };
}

#endif