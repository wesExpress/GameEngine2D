#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Engine/EngineDefines.h"

#include "RendererCommand.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Camera/Camera.h"

#include <glm/glm.hpp>

namespace Engine
{
    class Renderer
    {
        public:
            static void Init();
            static void BeginScene(const Camera& camera);
            static void EndScene();
            static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

            static void OnWindowResize(uint32_t width, uint32_t height);

            inline static RendererAPI::API Get() { return RendererAPI::GetAPI(); }
        private:
            struct SceneData
            {
                glm::mat4 m_viewProjectionMatrix;
            };

            static Scope<SceneData> s_sceneData;
    };
}

#endif
