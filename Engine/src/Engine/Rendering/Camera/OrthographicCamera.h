#ifndef __ORTHOGRAPHICCAMERA_H__
#define __ORTHOGRAPHICCAMERA_H__

#include "Camera.h"

namespace Engine
{
    class OrthographicCamera : public Camera
    {
        public:
            OrthographicCamera();
            OrthographicCamera(float left, float right, float top, float bottom);
            OrthographicCamera(float left, float right, float top, float bottom, float near, float far);

            virtual void Update() override;
    };
}

#endif