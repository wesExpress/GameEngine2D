#ifndef __RENDERCONTEXT_H__
#define __RENDERCONTEXT_H__

namespace Engine
{
    class RenderContext
    {
        public:
            virtual void Init() = 0;
            virtual void SwapBuffers() = 0;
    };
}

#endif