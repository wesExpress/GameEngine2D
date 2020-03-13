#include "CameraController.h"
#include "OrthographicCamera.h"
#include "EngineDefines.h"
#include "Input.h"
#include "Event/KeyCodes.h"

namespace Engine
{
    CameraController::CameraController(float aspectRatio)
        :
        m_aspectRatio(aspectRatio),
        m_camera(-aspectRatio * m_zoom, aspectRatio * m_zoom, -m_zoom, m_zoom)
    {}

    void CameraController::SetPos(const glm::vec3& position)
    {
        m_camera.SetPos(position);
    }

    void CameraController::SetRotation(float rotation)
    {
        m_camera.SetRotation(rotation);
    }

    void CameraController::OnUpdate(const Timestep& ts)
    {
        if (Input::IsKeyPressed(KEY_W) || Input::IsKeyPressed(KEY_UP))
        {
            cameraPos.y += cameraMoveSpeed * ts.GetTimeSeconds();
        }
        else if (Input::IsKeyPressed(KEY_S) || Input::IsKeyPressed(KEY_DOWN))
        {
            cameraPos.y -= cameraMoveSpeed * ts.GetTimeSeconds();
        }

        if (Input::IsKeyPressed(KEY_A) || Input::IsKeyPressed(KEY_LEFT))
        {
            cameraPos.x -= cameraMoveSpeed * ts.GetTimeSeconds();
        }
        else if (Input::IsKeyPressed(KEY_D) || Input::IsKeyPressed(KEY_RIGHT))
        {
            cameraPos.x += cameraMoveSpeed * ts.GetTimeSeconds();
        }

        if (Input::IsKeyPressed(KEY_Q))
        {
            cameraRotation -= cameraRotateSpeed * ts.GetTimeSeconds();
        }
        else if (Input::IsKeyPressed(KEY_E))
        {
            cameraRotation += cameraRotateSpeed * ts.GetTimeSeconds();
        }

        m_camera.SetPos(cameraPos);
        m_camera.SetRotation(cameraRotation);
    }

    void CameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<MouseScrolledEvent>(BIND_FN(CameraController::OnScroll));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_FN(CameraController::OnResize));
    }

    bool CameraController::OnScroll(MouseScrolledEvent& e)
    {
        m_zoom -= e.GetYDiff() * 0.25f;
        m_zoom = std::max(m_zoom, 0.25f);
        m_camera.SetProjection(-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom);

        return false;
    }

    bool CameraController::OnResize(WindowResizeEvent& e)
    {
        m_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_camera.SetProjection(-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom);

        return false;
    }
}