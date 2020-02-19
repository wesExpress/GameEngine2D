#include "CameraController.h"
#include "OrthographicCamera.h"

namespace Engine
{
    CameraController::CameraController()
    {
        m_camera = std::unique_ptr<Camera>(new OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f));
    }

    void CameraController::SetPos(const glm::vec3& position)
    {
        m_camera->SetPos(position);
    }

    void CameraController::SetRotation(float rotation)
    {
        m_camera->SetRotation(rotation);
    }
}