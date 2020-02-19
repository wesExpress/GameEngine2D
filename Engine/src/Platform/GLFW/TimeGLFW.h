#ifndef __TIMEGLFW_H__
#define __TIMEGLFW_H__

#include <GLFW/glfw3.h>

namespace Engine
{
    inline float GetTime() { return (float)glfwGetTime(); }
}

#endif