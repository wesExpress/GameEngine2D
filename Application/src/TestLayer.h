#ifndef __TESTLAYER_H__
#define __TESTLAYER_H__

#include <Engine.h>

class TestLayer : public Engine::Layer
{
    public:
        TestLayer();

        virtual void OnUpdate(const Engine::Timestep& ts) override;

    private:
        std::shared_ptr<Engine::Shader> m_shaderMultiColor;
        std::shared_ptr<Engine::VertexArray> m_triangleVA;

        std::shared_ptr<Engine::Shader> m_shaderBlue;
        std::shared_ptr<Engine::VertexArray> m_squareVA;

        Engine::CameraController m_cameraController;
        glm::vec3 m_cameraPosition;

        float cameraMoveSpeed = 5.0f;
        float cameraRotateSpeed = 180.0f;
        float cameraRotation = 0.0f;
        glm::vec3 squareTransform;
};

#endif