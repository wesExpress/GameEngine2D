#ifndef __INPUT_H__
#define __INPUT_H__

namespace Engine
{
    class Input
    {
        public:
            inline static bool IsKeyPressed(int keycode) { return m_instance->IsKeyPressedImpl(keycode); }
            inline static bool IsMouseButtonPressed(int button) { return m_instance->IsMouseButtonPressedImpl(button); }
            inline static std::pair<float, float> GetMousePos() { return m_instance->GetMousePosImpl(); }
            inline static float GetMouseX() { return m_instance->GetMouseX(); }
            inline static float GetMouseY() { return m_instance->GetMouseY(); }
        protected:
            virtual bool IsKeyPressedImpl(int keycode) const = 0;
            virtual bool IsMouseButtonPressedImpl(int button) const = 0;
            virtual std::pair<float, float> GetMousePosImpl() const = 0;
            virtual float GetMouseXImpl() const = 0;
            virtual float GetMouseYImpl() const = 0;
        private:
            static Input* m_instance;
    };
}

#endif