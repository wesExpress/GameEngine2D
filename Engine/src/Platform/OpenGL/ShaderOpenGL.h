#ifndef __SHADEROPENGL_H__
#define __SHADEROPENGL_H__

#include "Rendering/Shader.h"

namespace Engine
{
    class ShaderOpenGL : public Shader
    {
        public:
            ShaderOpenGL(const std::string& vertexSrc, const std::string& fragSrc);
            virtual ~ShaderOpenGL();

            virtual void Bind() const override;
            virtual void UnBind() const override;
        private:
            uint32_t m_rendererID;
    };
}

#endif