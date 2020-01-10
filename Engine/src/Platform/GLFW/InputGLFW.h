#ifndef __INPUTGLFW_H__
#define __INPUTGLFW_H__

#include "Engine/Input.h"

namespace Engine
{
    class InputGLFW : public Input
    {
        public:
            virtual bool IsKeyPressedImpl(int keycode) const override;
            virtual bool IsMouseButtonPressedImpl(int button) const override;
            virtual std::pair<float, float> GetMousePosImpl() const override;
            virtual float GetMouseXImpl() const override;
            virtual float GetMouseYImpl() const override;
    };
}

#endif