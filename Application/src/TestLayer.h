#ifndef __TESTLAYER_H__
#define __TESTLAYER_H__

#include <Engine.h>

class TestLayer : public Engine::Layer
{
    public:
        TestLayer();

        virtual void OnUpdate(const Engine::Timestep& ts) override;
        virtual void OnImGuiRender() override;
        virtual void OnEvent(Engine::Event& e) override;

    private:
        Engine::ShaderLibrary m_shaderLibrary;
    
        Engine::Ref<Engine::VertexArray> m_triangleVA;
        Engine::Ref<Engine::VertexArray> m_squareVA;

        Engine::Ref<Engine::Texture2D> m_texture;
        Engine::Ref<Engine::Texture2D> m_logo;

        Engine::CameraController m_cameraController;
        glm::vec3 m_cameraPosition;
        
        glm::vec3 squareTransform;
        glm::vec3 squareColor = { 0.3f, 0.2f, 0.8f};
};

#endif
