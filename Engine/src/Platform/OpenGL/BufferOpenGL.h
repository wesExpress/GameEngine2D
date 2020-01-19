#ifndef __BUFFEROPENGL_H__
#define __BUFFEROPENGL_H__

#include "Rendering/Buffer.h"

namespace Engine
{
    class VertexBufferOpenGL : public VertexBuffer
    {
        public:
            VertexBufferOpenGL(float* vertices, uint32_t size);
            virtual ~VertexBufferOpenGL();

            virtual void Bind() const override;
            virtual void UnBind() const override;

            virtual const BufferLayout& GetLayout() const override { return m_layout; }
            virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; }

        private:
            uint32_t m_rendererID;
            BufferLayout m_layout;
    };

    class IndexBufferOpenGL : public IndexBuffer
    {
        public:
            IndexBufferOpenGL(uint32_t* indices, uint32_t count);
            virtual ~IndexBufferOpenGL();

            virtual void Bind() const override;
            virtual void UnBind() const override;

            inline virtual uint32_t GetCount() const override { return m_count; }

        private:
            uint32_t m_rendererID;
            uint32_t m_count;
    };
}

#endif