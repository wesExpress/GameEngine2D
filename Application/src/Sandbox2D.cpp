#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <AL/al.h>

Sandbox2D::Sandbox2D()
	:
	Engine::Layer("Sandbox2D"), m_cameraController(1280.0f / 720.0f), 
    m_audioMaster(new Engine::AudioMaster()), m_audioSource1(new Engine::ALSource()), m_audioSource2(new Engine::ALSource())
{}

void Sandbox2D::OnAttach()
{
    std::string checkerboard = "textures/Checkerboard.png";
    m_texture = Engine::Texture2D::Create(ASSET_PATH + checkerboard);

    //m_audioMaster->LoadSound(ASSET_PATH + "sounds/bounce.wav", "bounce");
    m_audioSource1->SetBuffer(ASSET_PATH + "sounds/bounce.wav", "bounce", m_audioMaster);
    m_audioSource2->SetBuffer(ASSET_PATH + "sounds/bounce.wav", "bounce", m_audioMaster);
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(const Engine::Timestep& ts)
{
    m_cameraController.OnUpdate(ts);

    if (Engine::Input::IsKeyPressed(KEY_P))
    {
        m_audioSource1->Play();
    }
    else if (Engine::Input::IsKeyPressed(KEY_O))
    {
        m_audioSource1->Pause();
    }
    else if (Engine::Input::IsKeyPressed(KEY_U))
    {
        m_audioSource1->Stop();
    }

    if (Engine::Input::IsKeyPressed(KEY_T))
    {
        m_audioSource2->Play();
    }

    if (Engine::Input::IsKeyPressed(KEY_M))
    {
        m_audioSource2->SetPitch(2.0f);
    }

    Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Engine::RenderCommand::Clear();

    Engine::Renderer2D::BeginScene(m_cameraController.GetCamera());
    Engine::Renderer2D::DrawQuad(squarePos, { 0.8f, 0.8f }, squareColor);
    Engine::Renderer2D::DrawQuad({ 0.0f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    Engine::Renderer2D::DrawTexture({ 0.2f, 0.5f, -0.1f }, { 10.0f, 10.0f }, glm::vec4(1.0f), 10.0f, m_texture);
    Engine::Renderer2D::DrawTexture({ 0.2f, 0.5f }, { 1.0f, 1.0f }, {1.0f, 0.8f, 0.8f, 1.0f}, 10.0f, m_texture);
    Engine::Renderer2D::EndScene();

    Engine::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
    ImGui::SliderFloat3("Square Position", glm::value_ptr(squarePos), -1.0f, 1.0f);
    ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& e)
{
    m_cameraController.OnEvent(e);
}
