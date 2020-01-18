#include <Engine.h>
#include "imgui.h"

class TestLayer : public Engine::Layer
{
    public:
        TestLayer()
        :
        Engine::Layer("Test Layer")
        {}

        virtual void OnUpdate() override
        {
        }

        virtual void OnImGuiRender() override
        {
            ImGui::Begin("Test");
            ImGui::Text("Text");
            ImGui::End();
        }
};

class Application : public Engine::EngineApp
{
    public:
        Application()
        {
            PushLayer(new TestLayer());
        }

        ~Application()
        {

        }
}; 

Engine::EngineApp* Engine::CreateApplication()
{
    return new Application();
}