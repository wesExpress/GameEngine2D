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

            virtual void UploadUniformInt(const std::string& name, const int& value) override;

            virtual void UploadUniformFloat(const std::string& name, const float& value) override;
            virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vec) override;
            virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vec) override;
            virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vec) override;

            virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
            virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
        private:
            uint32_t m_rendererID;
    };
}

#endif