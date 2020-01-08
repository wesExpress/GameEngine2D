#ifndef __IMGUILAYER_H__
#define __IMGUILAYER_H__

#include "Layer.h"

#include "Event/Event.h"
#include "Event/KeyboardEvent.h"
#include "Event/MouseEvent.h"
#include "Event/WindowEvent.h"

class ImGuiLayer : public Layer
{
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        void OnUpdate() override;
        void OnAttach() override;
        void OnDetach() override;
        void OnEvent(Event& e) override;
    private:
        bool OnMouseMoved(MouseMovedEvent& e);
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);

        bool OnKeyPressed(KeyPressedEvent& e);
        bool OnKeyReleased(KeyReleasedEvent& e);
        bool OnKeyTyped(KeyTypedEvent& e);
        
        bool OnWindowResize(WindowResizeEvent& e);
    private:
        float m_time = 0.0f;
};

#endif