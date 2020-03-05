#include "TextureOpenGL.h"

#include <glad/glad.h>
#include "stb_image.h"

namespace Engine
{
    Texture2DOpenGL::Texture2DOpenGL(const std::string& path)
    :
    m_path(path)
    {
        stbi_set_flip_vertically_on_load(1);

        int width, height, channels;
        auto* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        ENGINE_ASSERT(data, stbi_failure_reason());
        m_width = width;
        m_height = height;
        
        GLuint internalFormat = 0, dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        #ifdef __APPLE__
        glGenTextures(1, &m_rendererID);
        glBindTexture(GL_TEXTURE_2D, m_rendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
        #else
        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
        glTextureStorage2D(m_rendererID, 1, internalFormat, m_width, m_height);

        glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);
        #endif

        stbi_image_free(data);
    }

    Texture2DOpenGL::~Texture2DOpenGL()
    {
        glDeleteTextures(1, &m_rendererID);
    }

    void Texture2DOpenGL::Bind(uint32_t slot) const
    {
        #ifdef __APPLE__
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_rendererID);
        #else
        glBindTextureUnit(slot, m_rendererID);
        #endif
    }
}
