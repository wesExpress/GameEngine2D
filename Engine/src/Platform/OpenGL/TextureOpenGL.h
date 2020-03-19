#ifndef __TEXTUREOPENGL_H__
#define __TEXTUREOPENGL_H__

#include "Rendering/Texture.h"
#include <glad/glad.h>

namespace Engine
{
    class Texture2DOpenGL : public Texture2D
    {
        public:
            Texture2DOpenGL(uint32_t width, uint32_t height);
            Texture2DOpenGL(const std::string& path);
            virtual ~Texture2DOpenGL();

            inline virtual uint32_t GetHeight() const override { return m_height; }
            inline virtual uint32_t GetWidth() const override { return m_height; }

            void SetData(void* data, uint32_t size) override;

            virtual void Bind(uint32_t slot = 0) const override;
        private:
            std::string m_path;

            uint32_t m_width, m_height;
            uint32_t m_rendererID;
            GLenum m_internalFormat, m_dataForamt;
    };
}

#endif