#include "OpenGL/RenderContextOpenGL.h"
#include "Logging.h"

namespace Engine
{
    RenderContextOpenGL::RenderContextOpenGL(GLFWwindow* windowHandle)
    :
    m_windowHandle(windowHandle)
    {
        if (m_windowHandle == NULL)
        {
            ENGINE_ERROR("Window handle is NULL!");
        }
    }

    void RenderContextOpenGL::Init()
    {
        glfwMakeContextCurrent(m_windowHandle);
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            ENGINE_ERROR("Glad failed to initialize!");
        }
    }

    void RenderContextOpenGL::SwapBuffers()
    {
        glfwSwapBuffers(m_windowHandle);
    }
}