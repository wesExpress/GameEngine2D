#include "Renderer.h"

namespace Engine
{
    Scope<Renderer::SceneData> Renderer::s_sceneData = std::make_unique<Renderer::SceneData>(Renderer::SceneData());

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
}
