#include "Renderer.h"

namespace Engine
{
    void Renderer::BeginScene()
    {

    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
    {
        shader->Bind();
        
        vertexArray->Bind();
        RendererCommand::DrawIndexed(vertexArray);
    }
}