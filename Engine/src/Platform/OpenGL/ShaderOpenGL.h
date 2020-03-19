#ifndef __SHADEROPENGL_H__
#define __SHADEROPENGL_H__

#include <glad/glad.h>

#include "Rendering/Shader.h"

namespace Engine
{
    class ShaderOpenGL : public Shader
    {
        public:
            ShaderOpenGL(const std::string& filename);
            ShaderOpenGL(const std::string& name, const std::string& vertexSrc, const std::string& fragSrc);
            virtual ~ShaderOpenGL();

            virtual const std::string& GetName() const override { return m_name; }
        
            virtual void Bind() const override;
            virtual void UnBind() const override;

            virtual void SetInt(const std::string& name, int value) override;
            virtual void SetFloat(const std::string& name, float value) override;
            virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
            virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
            virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

            virtual void UploadUniformInt(const std::string& name, const int& value) override;

            virtual void UploadUniformFloat(const std::string& name, const float& value) override;
            virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vec) override;
            virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vec) override;
            virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vec) override;

            virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
            virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
        private:
            std::string ParseString(const std::string& filePath);
            std::string ReadFile(const std::string& filename);
            std::unordered_map<GLenum, std::string> PreProcess(const std::string& fileSource);
            void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
        private:
            uint32_t m_rendererID;
            std::string m_name;
    };
}

#endif
