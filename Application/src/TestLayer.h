#ifndef __TESTLAYER_H__
#define __TESTLAYER_H__

#include <Engine.h>

class TestLayer : public Engine::Layer
{
    public:
        TestLayer();

        virtual void OnUpdate(const Engine::Timestep& ts) override;
        virtual void OnImGuiRender() override;

    private:
        std::shared_ptr<Engine::Shader> m_shaderMultiColor;
        std::shared_ptr<Engine::VertexArray> m_triangleVA;

        std::shared_ptr<Engine::Shader> m_squareShader;
        std::shared_ptr<Engine::VertexArray> m_squareVA;

        Engine::CameraController m_cameraController;
        glm::vec3 m_cameraPosition;

        float cameraMoveSpeed = 5.0f;
        float cameraRotateSpeed = 180.0f;
        float cameraRotation = 0.0f;
        glm::vec3 squareTransform;
        glm::vec3 squareColor = { 0.3f, 0.2f, 0.8f};
};

#endif