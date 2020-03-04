#include "TestLayer.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

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

    // multi color shader
    
    std::string multiColorShaderVertexSrc = R"(
        #version 330

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        uniform mat4 u_viewProjection;
        uniform mat4 u_transform;

        out vec3 v_position;
        out vec4 v_color;

        void main()
        {
            v_position = vec3(a_Position);
            v_color = a_Color;
            gl_Position = u_viewProjection * u_transform * vec4(a_Position, 1.0);
        }
    )";

    std::string multiColorShaderFragmentSrc = R"(
        #version 330

        layout(location = 0) out vec4 color;

        in vec3 v_position;
        in vec4 v_color;

        void main()
        {
            color = vec4(v_position*0.5 + 0.5, 1.0);
            color = v_color;
        }
    )";

    m_shaderMultiColor.reset(Engine::Shader::Create(multiColorShaderVertexSrc, multiColorShaderFragmentSrc));

    // blue color shader
    
    std::string singleColorVertexSrc = R"(
        #version 330

        layout(location = 0) in vec3 a_Position;

        uniform mat4 u_viewProjection;
        uniform mat4 u_transform;

        out vec3 v_position;

        void main()
        {
            v_position = vec3(a_Position);
            gl_Position = u_viewProjection * u_transform * vec4(a_Position, 1.0);
        }
    )";

    std::string singleColorFragSrc = R"(
        #version 330

        layout(location = 0) out vec4 color;

        in vec3 v_position;

        uniform vec3 u_color;

        void main()
        {
            color = vec4(u_color, 1.0);
        }
    )";

    m_squareShader.reset(Engine::Shader::Create(singleColorVertexSrc, singleColorFragSrc));

    // texture
    std::string textureVertexSrc = R"(
        #version 330

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec2 a_texCoord;

        uniform mat4 u_viewProjection;
        uniform mat4 u_transform;

        out vec2 v_texCoord;

        void main()
        {
            v_texCoord = a_texCoord;
            gl_Position = u_viewProjection * u_transform * vec4(a_Position, 1.0);
        }
    )";

    std::string textureFragSrc = R"(
        #version 330

        layout(location = 0) out vec4 color;

        in vec2 v_texCoord;

        uniform sampler2D u_texture;

        void main()
        {
            color = texture(u_texture, v_texCoord);
        }
    )";

    m_textureShader.reset(Engine::Shader::Create(textureVertexSrc, textureFragSrc));

    const char* texture_path;
#ifdef __APPLE__
        texture_path = "/Users/wesleypeters/Documents/random_code/GameEngine2D/Application/assets/textures/Checkerboard.png";
#else
        texture_path = "C:/Users/wcp/source/projects/GameEngine2D/Application/assets/textures/Checkerboard.png";
#endif
    m_texture = Engine::Texture2D::Create(texture_path);
    m_textureShader->Bind();
    m_textureShader->UploadUniformInt("u_texture", 0);
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
    
    m_squareShader->Bind();
    m_squareShader->UploadUniformFloat3("u_color", squareColor);

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    for(int y = 0; y < 20; y++)
    {
        for (int x = 0; x<20; x++)
        {
            glm::vec3 pos(x*0.11f, y*0.11f, 0.0f);
            Engine::Renderer::Submit(m_squareShader, m_squareVA, glm::translate(glm::mat4(1.0f), pos)*scale);
        }
    }

    m_texture->Bind();
    Engine::Renderer::Submit(m_textureShader, m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Engine::Renderer::EndScene();
}

void TestLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor));
    ImGui::End();
}
