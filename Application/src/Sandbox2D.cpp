#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:
	Engine::Layer("Sandbox2D"), m_cameraController(1280.0f / 720.0f)
{}

void Sandbox2D::OnAttach()
{
    std::string checkerboard = "textures/Checkerboard.png";
    m_texture = Engine::Texture2D::Create(ASSET_PATH + checkerboard);
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(const Engine::Timestep& ts)
{
    m_cameraController.OnUpdate(ts);

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
