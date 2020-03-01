#include "ShaderOpenGL.h"
#include "Logging.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
    ShaderOpenGL::ShaderOpenGL(const std::string& vertexSrc, const std::string& fragSrc)
    {
        // Create an empty vertex shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const GLchar* source = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        // Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
            
            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            ENGINE_ERROR("Vertex shader compilation error: {0}", infoLog.data());
            
            return;
        }

        // Create an empty fragment shader handle
        GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        source = fragSrc.c_str();
        glShaderSource(fragShader, 1, &source, 0);

        // Compile the fragment shader
        glCompileShader(fragShader);

        glGetShaderiv(fragShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragShader, maxLength, &maxLength, &infoLog[0]);
            
            // We don't need the shader anymore.
            glDeleteShader(fragShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(fragShader);

            ENGINE_ERROR("Fragment shader compilation error: {0}", infoLog.data());

            return;
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_rendererID = glCreateProgram();
        GLuint program = m_rendererID;

        // Attach our shaders to our program
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragShader);

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            
            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragShader);

            ENGINE_ERROR("Shader linking error!");

            return;
        }

        // Always detach shaders after a successful link.
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragShader);

        ENGINE_INFO("Created OpenGL shaders.");
    }

    ShaderOpenGL::~ShaderOpenGL()
    {
        glDeleteProgram(m_rendererID);
    }

    void ShaderOpenGL::Bind() const
    {
        glUseProgram(m_rendererID);
    }

    void ShaderOpenGL::UnBind() const
    {
        glUseProgram(0);
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