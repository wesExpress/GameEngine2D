#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "RendererCommand.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Camera/Camera.h"

namespace Engine
{
    class Renderer
    {
        public:
            static void BeginScene(const Camera& camera);
            static void EndScene();
            static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

            inline static RendererAPI::API Get() { return RendererAPI::GetAPI(); }
        private:
            struct SceneData
            {
                glm::mat4 m_viewProjectionMatrix;
            };

            static std::unique_ptr<SceneData> s_sceneData;
    };
}

#endif