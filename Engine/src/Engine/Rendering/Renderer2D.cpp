#include "Renderer2D.h"

#include "Shader.h"
#include "VertexArray.h"
#include "RenderCommand.h"

namespace Engine
{
	struct RenderData2D
	{
		Ref<Shader> textureShader;
		Ref<Texture2D> whiteTexture;
		Ref<VertexArray> vertexArray;
	};

	static RenderData2D* s_data;

	void Renderer2D::Init()
	{
		s_data = new RenderData2D();

		s_data->vertexArray = Engine::VertexArray::Create();

		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Engine::Ref<Engine::VertexBuffer> squareVB;
		squareVB = Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Engine::ShaderDataType::Float3, "a_Position"},
			{ Engine::ShaderDataType::Float2, "a_TexCoord"}
		});
		s_data->vertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Engine::Ref<Engine::IndexBuffer> squareIB;
		squareIB = Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_data->vertexArray->SetIndexBuffer(squareIB);

		s_data->whiteTexture = Engine::Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_data->whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_data->textureShader = Engine::Shader::Create(ASSET_PATH + "shaders/Texture.glsl");
		s_data->textureShader->Bind();
		s_data->textureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_data;
	}

	void Renderer2D::BeginScene(const Camera& camera)
	{	
		s_data->textureShader->Bind();
		s_data->textureShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawTexture(pos, size, color, 1.0f, s_data->whiteTexture);
	}

	void Renderer2D::DrawTexture(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawTexture({ pos.x, pos.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawTexture(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawTexture(pos, size, glm::vec4(1.0f), 1.0f, texture);
	}

	void Renderer2D::DrawTexture(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, float scale, const Ref<Texture2D>& texture)
	{
		DrawTexture({ pos.x, pos.y, 0.0f }, size, color, scale, texture);
	}

	void Renderer2D::DrawTexture(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float scale, const Ref<Texture2D>& texture)
	{
		s_data->textureShader->Bind();
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->textureShader->SetMat4("u_transform", transform);
		s_data->textureShader->SetFloat4("u_color", color);
		s_data->textureShader->SetFloat("u_scale", scale);

		s_data->vertexArray->Bind();
		RenderCommand::DrawIndexed(s_data->vertexArray);
	}
}
