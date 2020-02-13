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

            virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
    };
}

#endif