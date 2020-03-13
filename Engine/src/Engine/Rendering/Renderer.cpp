#include "Renderer.h"

namespace Engine
{
    Scope<Renderer::SceneData> Renderer::s_sceneData = std::make_unique<Renderer::SceneData>(Renderer::SceneData());

    void Renderer::Init()
    {
        RendererCommand::Init();
    }

    void Renderer::BeginScene(const Camera& camera)
    {
        s_sceneData->m_viewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->Bind();
        shader->UploadUniformMat4("u_viewProjection", s_sceneData->m_viewProjectionMatrix);
        shader->UploadUniformMat4("u_transform", transform);
        
        vertexArray->Bind();
        RendererCommand::DrawIndexed(vertexArray);
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RendererCommand::SetViewPort(0, 0, width, height);
    }
}
