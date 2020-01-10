#include "InputGLFW.h"
#include "Engine/EngineApp.h"
#include <GLFW/glfw3.h>

namespace Engine
{
    Input* Input::m_instance = new InputGLFW();

    bool InputGLFW::IsKeyPressedImpl(int keycode) const
    {
        auto window = static_cast<GLFWwindow*>(Engine::EngineApp::Get().GetWindow().GetWindow());
        auto status = glfwGetKey(window, keycode);
        return (status == GLFW_PRESS) || (status == GLFW_REPEAT);
    }

    bool InputGLFW::IsMouseButtonPressedImpl(int button) const
    {
        auto window = static_cast<GLFWwindow*>(Engine::EngineApp::Get().GetWindow().GetWindow());
        auto status = glfwGetMouseButton(window, button);
        return status == GLFW_PRESS;
    }

    std::pair<float, float> InputGLFW::GetMousePosImpl() const
    {
        auto window = static_cast<GLFWwindow*>(Engine::EngineApp::Get().GetWindow().GetWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return {(float)x, (float)y};
    }

    float InputGLFW::GetMouseXImpl() const
    {
        return GetMousePosImpl().first;
    }

    float InputGLFW::GetMouseYImpl() const
    {
        return GetMousePosImpl().second;
    }
}