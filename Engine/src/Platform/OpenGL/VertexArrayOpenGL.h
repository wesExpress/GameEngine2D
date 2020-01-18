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

        private:
            uint32_t m_rendererID;
    };
}

#endif