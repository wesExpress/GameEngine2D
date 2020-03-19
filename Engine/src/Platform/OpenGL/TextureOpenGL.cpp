#include "TextureOpenGL.h"

#include "EngineDefines.h"

#include "stb_image.h"

namespace Engine
{
    Texture2DOpenGL::Texture2DOpenGL(uint32_t width, uint32_t height)
        :
        m_width(width), m_height(height)
    {
        m_internalFormat = GL_RGBA8;
        m_dataForamt = GL_RGBA;

#ifdef __APPLE__
        glGenTextures(1, &m_rendererID);
        glBindTexture(GL_TEXTURE_2D, m_rendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
#else
        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
        glTextureStorage2D(m_rendererID, 1, m_internalFormat, m_width, m_height);

        glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
#endif
    }

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
        
        if (channels == 4)
        {
            m_internalFormat = GL_RGBA8;
            m_dataForamt = GL_RGBA;
        }
        else if (channels == 3)
        {
            m_internalFormat = GL_RGB8;
            m_dataForamt = GL_RGB;
        }

        #ifdef __APPLE__
        glGenTextures(1, &m_rendererID);
        glBindTexture(GL_TEXTURE_2D, m_rendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_dataForamt, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
        #else
        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
        glTextureStorage2D(m_rendererID, 1, m_internalFormat, m_width, m_height);

        glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, m_dataForamt, GL_UNSIGNED_BYTE, data);
        #endif

        stbi_image_free(data);
    }

    void Texture2DOpenGL::SetData(void* data, uint32_t size)
    {
        uint32_t bpp = (m_dataForamt == GL_RGBA) ? 4 : 3;
        ENGINE_ASSERT((size == m_width * m_height * bpp), "Incorrect texture size data!");

#ifdef __APPLE__
        glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_dataForamt, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
#else
        glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, m_dataForamt, GL_UNSIGNED_BYTE, data);
#endif
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
