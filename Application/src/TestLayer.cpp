#include "TestLayer.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>

TestLayer::TestLayer()
:
Engine::Layer("Test Layer"), m_cameraPosition(0.0f), squareTransform(0.0f)
{
    // triangle rendering

    m_triangleVA.reset(Engine::VertexArray::Create());

    float triangleVertices[3 * 7] =
    {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.3f, 0.8f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.3f, 0.2f, 0.8f, 1.0f,
        0.0f,  0.5f, 0.0f, 0.7f, 0.8f, 0.2f, 1.0f
    };

    Engine::Ref<Engine::VertexBuffer> triangleVB;
    triangleVB.reset(Engine::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
    triangleVB->SetLayout({
        { Engine::ShaderDataType::Float3, "a_Position"},
        { Engine::ShaderDataType::Float4, "a_Color"}
    });
    m_triangleVA->AddVertexBuffer(triangleVB);

    uint32_t triangleIndices[3] = { 0, 1, 2 };
    Engine::Ref<Engine::IndexBuffer> triangleIB;
    triangleIB.reset(Engine::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
    m_triangleVA->SetIndexBuffer(triangleIB);

    // square rendering

    m_squareVA.reset(Engine::VertexArray::Create());

    float squareVertices[5 * 4] =
    {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    Engine::Ref<Engine::VertexBuffer> squareVB;
    squareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({
        { Engine::ShaderDataType::Float3, "a_Position"},
        { Engine::ShaderDataType::Float2, "a_TexCord"}
    });
    m_squareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Engine::Ref<Engine::IndexBuffer> squareIB;
    squareIB.reset(Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_squareVA->SetIndexBuffer(squareIB);
    
    std::string path;
    #ifdef __APPLE__
            path = "/Users/wesleypeters/Documents/random_code/GameEngine2D/Application/assets/";
    #else
            path = "C:/Users/wcp/source/projects/GameEngine2D/Application/assets/";
    #endif
    
    m_shaderLibrary.Add(Engine::Shader::Create(path+"shaders/SingleColor.glsl"));
    m_shaderLibrary.Add(Engine::Shader::Create(path+"shaders/MultiColor.glsl"));

    std::string checkerboard = "textures/Checkerboard.png";
    std::string logo = "textures/ChernoLogo.png";

    m_texture = Engine::Texture2D::Create(path+checkerboard);
    m_logo = Engine::Texture2D::Create(path+logo);
    
    auto shader = m_shaderLibrary.Load(path+"shaders/Texture.glsl");
    shader->Bind();
    shader->UploadUniformInt("u_texture", 0);
}

void TestLayer::OnUpdate(const Engine::Timestep& ts)
{
    //CLIENT_TRACE("Delta time: {0}", ts.GetTimeSeconds());

    if(Engine::Input::IsKeyPressed(KEY_W) || Engine::Input::IsKeyPressed(KEY_UP))
    {
        m_cameraPosition.y += cameraMoveSpeed * ts.GetTimeSeconds();
    }
    else if(Engine::Input::IsKeyPressed(KEY_S) || Engine::Input::IsKeyPressed(KEY_DOWN))
    {
        m_cameraPosition.y -= cameraMoveSpeed * ts.GetTimeSeconds();
    }

    if(Engine::Input::IsKeyPressed(KEY_A) || Engine::Input::IsKeyPressed(KEY_LEFT))
    {
        m_cameraPosition.x -= cameraMoveSpeed * ts.GetTimeSeconds();
    }
    else if(Engine::Input::IsKeyPressed(KEY_D) || Engine::Input::IsKeyPressed(KEY_RIGHT))
    {
        m_cameraPosition.x += cameraMoveSpeed * ts.GetTimeSeconds();
    }

    if(Engine::Input::IsKeyPressed(KEY_Q))
    {
        cameraRotation -= cameraRotateSpeed * ts.GetTimeSeconds();
    }
    else if(Engine::Input::IsKeyPressed(KEY_E))
    {
        cameraRotation += cameraRotateSpeed * ts.GetTimeSeconds();
    }

    if(Engine::Input::IsKeyPressed(KEY_J))
    {
        squareTransform.x -= cameraMoveSpeed * ts.GetTimeSeconds();
    }
    else if(Engine::Input::IsKeyPressed(KEY_L))
    {
        squareTransform.x += cameraMoveSpeed * ts.GetTimeSeconds();
    }

    if(Engine::Input::IsKeyPressed(KEY_I))
    {
        squareTransform.y -= cameraMoveSpeed * ts.GetTimeSeconds();
    }
    else if(Engine::Input::IsKeyPressed(KEY_K))
    {
        squareTransform.y += cameraMoveSpeed * ts.GetTimeSeconds();
    }

    m_cameraController.SetPos(m_cameraPosition);
    m_cameraController.SetRotation(cameraRotation);

    Engine::RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Engine::RendererCommand::Clear();

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
