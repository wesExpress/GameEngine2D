#ifndef __CAMERACONTROLLER_H__
#define __CAMERACONTROLLER_H__

#include "Camera.h"
#include "Event/Event.h"
#include "Event/KeyboardEvent.h"

namespace Engine
{
    class CameraController
    {
        public:
            CameraController();

            Camera GetCamera() { return *m_camera; }
            const Camera GetCamera() const { return *m_camera; }

            void OnEvent(Event& e);
        private:
            bool OnKeyPressed(KeyPressedEvent& e);
        private:
            std::unique_ptr<Camera> m_camera;
    };
}

#endif