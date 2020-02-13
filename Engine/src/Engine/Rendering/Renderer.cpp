#include "Renderer.h"

namespace Engine
{
    std::unique_ptr<Renderer::SceneData> Renderer::s_sceneData = std::make_unique<Renderer::SceneData>(Renderer::SceneData());

    void Renderer::BeginScene(const Camera& camera)
    {
        s_sceneData->m_viewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
    {
        shader->Bind();
        shader->UploadUniformMat4("u_viewProjection", s_sceneData->m_viewProjectionMatrix);
        
        vertexArray->Bind();
        RendererCommand::DrawIndexed(vertexArray);
    }
}