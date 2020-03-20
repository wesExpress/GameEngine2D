#include "TestLayer.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>

TestLayer::TestLayer()
:
Engine::Layer("Test Layer"), m_cameraController(1280.0f / 720.0f), m_cameraPosition(0.0f), squareTransform(0.0f)
{
    // triangle rendering

    m_triangleVA = Engine::VertexArray::Create();

    float triangleVertices[3 * 7] =
    {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.3f, 0.8f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.3f, 0.2f, 0.8f, 1.0f,
        0.0f,  0.5f, 0.0f, 0.7f, 0.8f, 0.2f, 1.0f
    };

    Engine::Ref<Engine::VertexBuffer> triangleVB;
    triangleVB = Engine::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices));
    triangleVB->SetLayout({
        { Engine::ShaderDataType::Float3, "a_Position"},
        { Engine::ShaderDataType::Float4, "a_Color"}
    });
    m_triangleVA->AddVertexBuffer(triangleVB);

    uint32_t triangleIndices[3] = { 0, 1, 2 };
    Engine::Ref<Engine::IndexBuffer> triangleIB;
    triangleIB = Engine::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t));
    m_triangleVA->SetIndexBuffer(triangleIB);

    // square rendering

    m_squareVA = Engine::VertexArray::Create();

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
        { Engine::ShaderDataType::Float2, "a_TexCord"}
    });
    m_squareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Engine::Ref<Engine::IndexBuffer> squareIB;
    squareIB = Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    m_squareVA->SetIndexBuffer(squareIB);
    
    m_shaderLibrary.Add(Engine::Shader::Create(ASSET_PATH+"shaders/SingleColor.glsl"));
    m_shaderLibrary.Add(Engine::Shader::Create(ASSET_PATH+"shaders/MultiColor.glsl"));

    std::string checkerboard = "textures/Checkerboard.png";
    std::string logo = "textures/ChernoLogo.png";

    m_texture = Engine::Texture2D::Create(ASSET_PATH+checkerboard);
    m_logo = Engine::Texture2D::Create(ASSET_PATH+logo);
    
    auto shader = m_shaderLibrary.Load(ASSET_PATH+"shaders/Texture.glsl");
    shader->Bind();
    shader->UploadUniformInt("u_texture", 0);
}

void TestLayer::OnUpdate(const Engine::Timestep& ts)
{
    //CLIENT_TRACE("Delta time: {0}", ts.GetTimeSeconds());
    m_cameraController.OnUpdate(ts);

    Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Engine::RenderCommand::Clear();

    Engine::Renderer::BeginScene(m_cameraController.GetCamera());

    // triangle
    //Engine::Renderer::Submit(m_shaderMultiColor, m_triangleVA);
    
    auto shader = m_shaderLibrary.Get("SingleColor");
    shader->Bind();
    shader->UploadUniformFloat3("u_color", squareColor);

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    for(int y = 0; y < 20; y++)
    {
        for (int x = 0; x<20; x++)
        {
            glm::vec3 pos(x*0.11f, y*0.11f, 0.0f);
            Engine::Renderer::Submit(shader, m_squareVA, glm::translate(glm::mat4(1.0f), pos)*scale);
        }
    }

    m_texture->Bind();
    shader = m_shaderLibrary.Get("Texture");
    Engine::Renderer::Submit(shader, m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    m_logo->Bind();
    Engine::Renderer::Submit(shader, m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Engine::Renderer::EndScene();
}

void TestLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor));
    ImGui::End();
}

void TestLayer::OnEvent(Engine::Event& e)
{
    m_cameraController.OnEvent(e);
}
