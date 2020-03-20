#include "ShaderOpenGL.h"
#include "Logging.h"
#include "EngineDefines.h"

#include <glm/gtc/type_ptr.hpp>
#include <filesystem>

namespace Engine
{
    static GLenum ShaderTypeFromString(const std::string& type)
    {
        if (type == "vertex")
        {
            return GL_VERTEX_SHADER;
        }
        if (type == "fragment" || type == "pixel")
        {
            return GL_FRAGMENT_SHADER;
        }
        
        ENGINE_ASSERT(false, "Invalid shader type: {0}", type);
    }

    ShaderOpenGL::ShaderOpenGL(const std::string& fileName)
    {
        std::string fileSource = ReadFile(fileName);
        std::unordered_map<GLenum, std::string> shaderSources = PreProcess(fileSource);
        
        Compile(shaderSources);
        
        m_name = ParseString(fileName);
    }
    
    ShaderOpenGL::ShaderOpenGL(const std::string& name, const std::string& vertexSrc, const std::string& fragSrc)
    :
    m_name(name)
    {
        std::unordered_map<GLenum, std::string> shaderSources;
        
        shaderSources[GL_VERTEX_SHADER] = vertexSrc;
        shaderSources[GL_FRAGMENT_SHADER] = fragSrc;
        
        Compile(shaderSources);
    }

    ShaderOpenGL::~ShaderOpenGL()
    {
        glDeleteProgram(m_rendererID);
        ENGINE_WARN("Deleted OpenGL shader.");
    }

    std::string ShaderOpenGL::ParseString(const std::string& filePath)
    {
        std::string result;
        
        auto lastSlash = filePath.find_last_of("/\\");
        lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
        auto lastDot = filePath.rfind('.');
        auto count = (lastDot == std::string::npos) ? filePath.size() - lastSlash : lastDot - lastSlash;
        
        return filePath.substr(lastSlash, count);
    }

    std::string ShaderOpenGL::ReadFile(const std::string& filename)
    {
        std::string result;
        std::ifstream in(filename, std::ios::in | std::ios::binary);
        ENGINE_ASSERT(in, "Error reading shader file: {0}", filename);
        
        in.seekg(0, std::ios::end);
        result.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&result[0], result.size());
        in.close();
        
        return result;
    }

    std::unordered_map<GLenum, std::string> ShaderOpenGL::PreProcess(const std::string& fileSource)
    {
        const char* eolChar = "\r\n";
        const char* token = "#type";
        size_t tokenLength = strlen(token);
        
        std::unordered_map<GLenum, std::string> shaderSource;

        size_t pos = fileSource.find(token, 0);

        while (pos != std::string::npos)
        {
            size_t eolPos = fileSource.find_first_of(eolChar, pos);
            size_t typeStart = pos + tokenLength + 1;
            size_t nextLinePos = fileSource.find_first_not_of(eolChar, eolPos);
            std::string type = fileSource.substr(typeStart, eolPos - typeStart);
            
            size_t shaderStart = (nextLinePos == std::string::npos) ? fileSource.size() - 1 : nextLinePos;
            
            pos = fileSource.find(token, shaderStart);
            shaderSource[ShaderTypeFromString(type)] = fileSource.substr(nextLinePos, pos - shaderStart);
        }
        
        return shaderSource;
    }

    void ShaderOpenGL::Compile(const std::unordered_map<GLenum, std::string>& shaderSource)
    {
        GLuint program = glCreateProgram();
        ENGINE_ASSERT((shaderSource.size() <= 2), "Only two shader types are supported.");
        std::array<GLenum, 2> shaderIDs;
        int shaderIndex = 0;
        
        for (auto& kv : shaderSource)
        {
            GLenum type = kv.first;
            std::string source_str = kv.second;
            
            GLuint shader = glCreateShader(type);
            const GLchar* source = source_str.c_str();
            glShaderSource(shader, 1, &source, 0);
            
            glCompileShader(shader);
            
            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
                
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
                
                glDeleteShader(shader);

                ENGINE_ERROR("Shader compilation error: {0}", infoLog.data());
                
                break;
            }
            
            glAttachShader(program, shader);
            shaderIDs[shaderIndex++] = shader;
        }
        
        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            
            glDeleteProgram(program);
            
            for (auto shader : shaderIDs)
            {
                glDeleteShader(shader);
            }

            ENGINE_ERROR("Shader linking error!");
        }

        // Always detach shaders after a successful link.
        for (auto shader : shaderIDs)
        {
            glDetachShader(program, shader);
        }

        m_rendererID = program;
        
        ENGINE_TRACE("Created OpenGL shaders.");
    }

    void ShaderOpenGL::Bind() const
    {
        glUseProgram(m_rendererID);
    }

    void ShaderOpenGL::UnBind() const
    {
        glUseProgram(0);
    }

    void ShaderOpenGL::SetInt(const std::string& name, int value)
    {
        UploadUniformInt(name, value);
    }

    void ShaderOpenGL::SetFloat(const std::string& name, float value)
    {
        UploadUniformFloat(name, value);
    }

    void ShaderOpenGL::SetFloat3(const std::string& name, const glm::vec3& value)
    {
        UploadUniformFloat3(name, value);
    }

    void ShaderOpenGL::SetFloat4(const std::string& name, const glm::vec4& value)
    {
        UploadUniformFloat4(name, value);
    }

    void ShaderOpenGL::SetMat4(const std::string& name, const glm::mat4& value)
    {
        UploadUniformMat4(name, value);
    }

    void ShaderOpenGL::UploadUniformInt(const std::string& name, const int& value)
    {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform1i(location, value);
    }

    void ShaderOpenGL::UploadUniformFloat(const std::string& name, const float& value)
    {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform1f(location, value);
    }

    void ShaderOpenGL::UploadUniformFloat2(const std::string& name, const glm::vec2& vec)
    {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform2f(location, vec.x, vec.y);
    }

    void ShaderOpenGL::UploadUniformFloat3(const std::string& name, const glm::vec3& vec)
    {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform3f(location, vec.x, vec.y, vec.z);
    }

    void ShaderOpenGL::UploadUniformFloat4(const std::string& name, const glm::vec4& vec)
    {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
    }

    void ShaderOpenGL::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
    {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderOpenGL::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}
