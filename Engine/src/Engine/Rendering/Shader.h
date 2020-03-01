#ifndef __SHADER_H__
#define __SHADER_H__

#include <glm/glm.hpp>
namespace Engine
{
    class Shader
    {
        public:
            virtual ~Shader() {}

            virtual void Bind() const = 0;
            virtual void UnBind() const = 0;

            static Shader* Create(const std::string& vertexSrc, const std::string& fragSrc);

            virtual void UploadUniformInt(const std::string& name, const int& value) = 0;

            virtual void UploadUniformFloat(const std::string& name, const float& value) = 0;
            virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vec) = 0;
            virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vec) = 0;
            virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vec) = 0;

            virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
            virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
    };
}

#endif