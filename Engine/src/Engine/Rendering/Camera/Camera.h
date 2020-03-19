#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Logging.h"

namespace Engine
{
    class Camera
    {
        public:
            virtual ~Camera() {}
            virtual void Update() {}

            void SetPos(const glm::vec3& pos) { m_data.pos = pos; Update(); }
            void SetFOV(float fov) { m_data.fov = fov; Update(); }
            void SetAspectRatio(float aspectRatio) { m_data.aspectRatio = aspectRatio; Update(); }
            void SetNear(float nearClip) { m_data.nearClip = nearClip; Update(); }
            void SetFar(float farClip) { m_data.farClip = farClip; Update(); }
            void SetRotation(float rotation) { m_data.rotation = rotation; Update(); }

            inline const glm::vec3& GetPos() const { return m_data.pos; }
            inline const float GetFOV() const { return m_data.fov; }
            inline const float GetAspectRatio() const { return m_data.aspectRatio; }
            inline const float GetNear() const { return m_data.nearClip; }
            inline const float GetFar() const { return m_data.farClip; }
            inline const float GetRotation() const { return m_data.rotation; }
            inline const glm::mat4& GetViewMatrix() const { return m_data.view; }
            inline const glm::mat4& GetProjectionMatrix() const { return m_data.projection; }
            inline const glm::mat4& GetViewProjectionMatrix() const { return m_data.viewProjection; }
        protected:
            struct CameraData
            {
                glm::vec3 pos;
                float fov, aspectRatio, nearClip, farClip, rotation;

                glm::mat4 view;
                glm::mat4 projection;
                glm::mat4 viewProjection;

                CameraData()
                    :
                    pos(glm::vec3()), fov(65.0f), aspectRatio(4.0f/3.0f), nearClip(-1.0f), farClip(1.0f), rotation(0.0f)
                {}

                CameraData(const glm::vec3 pos, float fov, float aspectRatio, float nearClip, float farClip, float rotation)
                :
                pos(pos), fov(fov), aspectRatio(aspectRatio), nearClip(nearClip), farClip(farClip), rotation(rotation)
                {}
            };

            CameraData m_data;
    };
}

#endif
