#ifndef __SHADER_H__
#define __SHADER_H__

namespace Engine
{
    class Shader
    {
        public:
            virtual ~Shader() {}

            virtual void Bind() const = 0;
            virtual void UnBind() const = 0;

            static Shader* Create(const std::string& vertexSrc, const std::string& fragSrc);
    };
}

#endif