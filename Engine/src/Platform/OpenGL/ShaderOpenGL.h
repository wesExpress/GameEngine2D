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

            virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
        private:
            uint32_t m_rendererID;
    };
}

#endif