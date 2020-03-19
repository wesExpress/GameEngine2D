#ifndef __SHADER_H__
#define __SHADER_H__

#include "EngineDefines.h"
#include <glm/glm.hpp>

namespace Engine
{
    class Shader
    {
        public:
            virtual ~Shader() {}

            static Ref<Shader> Create(const std::string& filename);
            static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragSrc);

            virtual const std::string& GetName() const = 0;

            virtual void Bind() const = 0;
            virtual void UnBind() const = 0;

            virtual void SetInt(const std::string& name, int value) = 0;
            virtual void SetFloat(const std::string& name, float value) = 0;
            virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
            virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
            virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

            virtual void UploadUniformInt(const std::string& name, const int& value) = 0;

            virtual void UploadUniformFloat(const std::string& name, const float& value) = 0;
            virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vec) = 0;
            virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vec) = 0;
            virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vec) = 0;

            virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
            virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
    };

    class ShaderLibrary
    {
        public:
            void Add(const std::string& name, const Ref<Shader>& shader);
            void Add(const Ref<Shader>& shader);
            Ref<Shader> Load(const std::string& name);
            Ref<Shader> Get(const std::string& name);
        private:
            bool Exists(const std::string& name);
        private:
            std::unordered_map<std::string, Ref<Shader>> m_shaders;
    };
}

#endif
