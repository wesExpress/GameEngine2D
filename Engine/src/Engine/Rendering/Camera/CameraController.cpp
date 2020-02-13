#include "CameraController.h"
#include "OrthographicCamera.h"

#include "Event/KeyCodes.h"

namespace Engine
{
    CameraController::CameraController()
    {
        m_camera = std::unique_ptr<Camera>(new OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f));
    }

    void CameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(BIND_FN(CameraController::OnKeyPressed));
    }

    bool CameraController::OnKeyPressed(KeyPressedEvent& e)
    {
        glm::vec3 deltaPos = {0.0f,0.0f,0.0f};
        float rotation = 0;

        switch(e.GetKeyCode())
        {
            case KEY_W:
                deltaPos = {0.0f,-0.1f,0.0f};
                break;
            case KEY_S:
                deltaPos = {0.0f,0.1f,0.0f};
                break;
            case KEY_A:
                deltaPos = {-0.1f,0.0f,0.0f};
                break;
            case KEY_D:
                deltaPos = {0.1f,0.0f,0.0f};
                break;
            case KEY_Q:
                rotation = -1.0f;
                break;
            case KEY_E:
                rotation = 1.0f;
                break;
        }
        glm::vec3 newPos = m_camera->GetPos() + deltaPos;
        float newRotation = m_camera->GetRotation() + rotation;

        m_camera->SetPos(newPos);
        m_camera->SetRotation(newRotation);

        return true;
    }
}