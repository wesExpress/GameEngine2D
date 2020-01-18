#ifndef __RENDERAPI_H__
#define __RENDERAPI_H__

namespace Engine
{
    enum RenderAPI
    {
        None = 0,
        OpenGL
    };

    class Renderer
    {
        public:
            inline static RenderAPI Get() { return m_renderAPI; }
        private:
            static RenderAPI m_renderAPI;
    };
}

#endif