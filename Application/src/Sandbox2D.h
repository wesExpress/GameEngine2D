#ifndef __SANDBOX2D_H__
#define __SANDBOX2D_H__

#include <Engine.h>

class Sandbox2D : public Engine::Layer
{
	public:
		Sandbox2D();
		virtual ~Sandbox2D() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(const Engine::Timestep& ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Engine::Event& e) override;
	private:
		Engine::CameraController m_cameraController;

		Engine::Ref<Engine::Shader> m_singleColorShader;
		Engine::Ref<Engine::VertexArray> m_squareVA;

		Engine::Ref<Engine::Texture2D> m_texture;

		glm::vec4 squareColor = { 0.3f, 0.2f, 0.8f, 1.0f };
        glm::vec3 squarePos = {0.0f, 0.0f, 0.0f};

		Engine::Ref<Engine::AudioMaster> m_audioMaster;
		Engine::Ref<Engine::ALSource> m_audioSource;
};

#endif
