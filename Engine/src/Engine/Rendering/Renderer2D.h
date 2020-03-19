#ifndef __RENDERER2D_H__
#define __RENDERER2D_H__

#include <glm/glm.hpp>

#include "Camera/OrthographicCamera.h"
#include "Texture.h"

namespace Engine
{
	class Renderer2D
	{
		public:
			static void Init();
			static void Shutdown();

			static void BeginScene(const Camera& camera);
			static void EndScene();

			static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
			static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);

			static void DrawTexture(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture);
			static void DrawTexture(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture);
			static void DrawTexture(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, float scale, const Ref<Texture2D>& texture);
			static void DrawTexture(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float scale, const Ref<Texture2D>& texture);
	};
}

#endif
