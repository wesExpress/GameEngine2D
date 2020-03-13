#include "OrthographicCamera.h"
#include "Logging.h"
namespace Engine
{
    OrthographicCamera::OrthographicCamera()
    {
        m_data.view = glm::mat4(1.0f);
        m_data.projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

        m_data.viewProjection = m_data.projection * m_data.view;
    }

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    {
        m_data.view = glm::mat4(1.0f);
        m_data.projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

        m_data.viewProjection = m_data.projection * m_data.view;
    }

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float nearClip, float farClip)
    {
        m_data.view = glm::mat4(1.0f);

        m_data.nearClip = nearClip;
        m_data.farClip = farClip;

        m_data.projection = glm::ortho(left, right, bottom, top, m_data.nearClip, m_data.farClip);

        m_data.viewProjection = m_data.projection * m_data.view;
    }

    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        m_data.projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_data.viewProjection = m_data.projection * m_data.view;
    }

    void OrthographicCamera::Update()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_data.pos);
        transform *= glm::rotate(glm::mat4(1.0f), glm::radians(m_data.rotation), glm::vec3(0, 0, 1));

        m_data.view = glm::inverse(transform);
        m_data.viewProjection = m_data.projection * m_data.view;
    }
};