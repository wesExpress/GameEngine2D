#ifndef __ORTHOGRAPHICCAMERA_H__
#define __ORTHOGRAPHICCAMERA_H__

#include "Camera.h"

namespace Engine
{
    class OrthographicCamera : public Camera
    {
        public:
            OrthographicCamera();
            OrthographicCamera(float left, float right, float bottom, float top);
            OrthographicCamera(float left, float right, float bottom, float top, float nearClip , float farClip);

            void SetProjection(float left, float right, float bottom, float top);

            virtual void Update() override;
    };
}

#endif