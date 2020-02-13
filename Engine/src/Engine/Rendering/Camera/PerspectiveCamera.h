#ifndef __PERSPECTIVECAMERA_H__
#define __PERSPECTIVECAMERA_H__

#include "Camera.h"

namespace Engine
{
    class PerspectiveCamera : public Camera
    {
        public:
            PerspectiveCamera();
            PerspectiveCamera(float fov, float aspectRatio);
            PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip);

            virtual void Update() override;

        private:
            glm::vec3 m_xaxis;
            glm::vec3 m_yaxis;
            glm::vec3 m_zaxis;
    };
}

#endif