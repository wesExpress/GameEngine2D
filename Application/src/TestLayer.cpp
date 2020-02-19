#include "TestLayer.h"

TestLayer::TestLayer()
:
Engine::Layer("Test Layer"), m_cameraPosition(0.0f)
{
    // triangle rendering

    m_triangleVA.reset(Engine::VertexArray::Create());

    float triangleVertices[3 * 7] =
    {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.3f, 0.8f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.3f, 0.2f, 0.8f, 1.0f,
        0.0f,  0.5f, 0.0f, 0.7f, 0.8f, 0.2f, 1.0f
    };

    std::shared_ptr<Engine::VertexBuffer> triangleVB;
    triangleVB.reset(Engine::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
    triangleVB->SetLayout({
        { Engine::ShaderDataType::Float3, "a_Position"},
        { Engine::ShaderDataType::Float4, "a_Color"}
    });
    m_triangleVA->AddVertexBuffer(triangleVB);

    uint32_t triangleIndices[3] = { 0, 1, 2 };
    std::shared_ptr<Engine::IndexBuffer> triangleIB;
    triangleIB.reset(Engine::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
    m_triangleVA->SetIndexBuffer(triangleIB);

    // square rendering

    m_squareVA.reset(Engine::VertexArray::Create());

    float squareVertices[3 * 4] =
    {
        -0.75f, -0.75f, 0.0f,
        0.75f, -0.75f, 0.0f,
        0.75f,  0.75f, 0.0f,
        -0.75f,  0.75f, 0.0f
    };

    std::shared_ptr<Engine::VertexBuffer> squareVB;
    squareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({
        { Engine::ShaderDataType::Float3, "a_Position"}
    });
    m_squareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    std::shared_ptr<Engine::IndexBuffer> squareIB;
    squareIB.reset(Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_squareVA->SetIndexBuffer(squareIB);

    // multi color shader
    
    std::string multiColorShaderVertexSrc = R"(
        #version 330

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        uniform mat4 u_viewProjection;

        out vec3 v_position;
        out vec4 v_color;

        void main()
        {
            v_position = vec3(a_Position);
            v_color = a_Color;
            gl_Position = u_viewProjection * vec4(a_Position, 1.0);
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
    
    std::string blueShaderVertexSrc = R"(
        #version 330

        layout(location = 0) in vec3 a_Position;

        uniform mat4 u_viewProjection;

        out vec3 v_position;

        void main()
        {
            v_position = vec3(a_Position);
            gl_Position = u_viewProjection * vec4(a_Position, 1.0);
        }
    )";

    std::string blueShaderFragSrc = R"(
        #version 330

        layout(location = 0) out vec4 color;

        in vec3 v_position;

        void main()
        {
            color = vec4(0.2, 0.3, 0.8, 1.0);
        }
    )";

    m_shaderBlue.reset(Engine::Shader::Create(blueShaderVertexSrc, blueShaderFragSrc));
}

void TestLayer::OnUpdate(const Engine::Timestep& ts)
{
    CLIENT_TRACE("Delta time: {0}", ts.GetTimeSeconds());

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

    m_cameraController.SetPos(m_cameraPosition);
    m_cameraController.SetRotation(cameraRotation);

    Engine::RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Engine::RendererCommand::Clear();

    Engine::Renderer::BeginScene(m_cameraController.GetCamera());

    Engine::Renderer::Submit(m_shaderBlue, m_squareVA);
    Engine::Renderer::Submit(m_shaderMultiColor, m_triangleVA);

    Engine::Renderer::EndScene();
}