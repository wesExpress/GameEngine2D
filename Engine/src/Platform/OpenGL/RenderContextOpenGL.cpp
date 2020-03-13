#include "OpenGL/RenderContextOpenGL.h"
#include "Logging.h"
#include "EngineDefines.h"

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
        ENGINE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Glad failed to initialize!");

        ENGINE_INFO("OpenGL Info:");
        ENGINE_INFO("    Vendor:   {0}", glGetString(GL_VENDOR));
        ENGINE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));
        ENGINE_INFO("    Version:  {0}", glGetString(GL_VERSION));
    }

    void RenderContextOpenGL::SwapBuffers()
    {
        glfwSwapBuffers(m_windowHandle);
    }
}