#include "PerspectiveCamera.h"

#define UP_VEC glm::vec3(0.0f, 1.0f, 0.0f)

namespace Engine
{
    PerspectiveCamera::PerspectiveCamera()
    {
        m_data.view = glm::mat4(1.0f);
        m_data.projection = glm::perspective(glm::radians(m_data.fov), m_data.aspectRatio, m_data.nearClip, m_data.farClip);

        m_data.viewProjection = m_data.projection * m_data.view;
    }

    PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio)
    {
        m_data.view = glm::mat4(1.0f);

        m_data.fov = fov;
        m_data.aspectRatio = aspectRatio;

        m_data.projection = glm::perspective(glm::radians(m_data.fov), m_data.aspectRatio, -1.0f, 1.0f);

        m_data.viewProjection = m_data.projection * m_data.view;
    }

    PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip)
    {
        m_data.view = glm::mat4(1.0f);

        m_data.fov = fov;
        m_data.aspectRatio = aspectRatio;
        m_data.nearClip = nearClip;
        m_data.farClip = farClip;

        m_data.projection = glm::perspective(glm::radians(m_data.fov), m_data.aspectRatio, m_data.nearClip, m_data.farClip);

        m_data.viewProjection = m_data.projection * m_data.view;
    }

    void PerspectiveCamera::Update()
    {
        m_zaxis = glm::normalize(m_data.pos);
        m_xaxis = glm::normalize(glm::cross(UP_VEC, m_zaxis));
        m_yaxis = glm::cross(m_zaxis, m_xaxis);

        m_data.view = glm::lookAt(m_data.pos, {0.0f, 0.0f, 0.0f}, m_yaxis);
        m_data.viewProjection = m_data.projection * m_data.view;
    }
}