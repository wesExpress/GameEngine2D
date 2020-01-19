#include "EngineApp.h"
#include "Event/WindowEvent.h"
#include "Input.h"
#include "EngineDefines.h"

#include <glad/glad.h>

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Engine
{
    EngineApp* EngineApp::m_instance = nullptr;
    RenderAPI Renderer::m_renderAPI = RenderAPI::OpenGL;

    EngineApp::EngineApp()
    {   
        ENGINE_ASSERT(!m_instance, "App already exists!");
        m_instance = this;

        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(BIND_FN(EngineApp::OnEvent));

        m_imguiLayer = new ImGuiLayer();
        PushOverlay(m_imguiLayer);

        // triangle rendering

        m_triangleVA.reset(VertexArray::Create());

        float triangleVertices[3 * 7] =
        {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.3f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.3f, 0.2f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.7f, 0.8f, 0.2f, 1.0f
        };

        std::shared_ptr<VertexBuffer> triangleVB;
        triangleVB.reset(VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
        triangleVB->SetLayout({
            { ShaderDataType::Float3, "a_Position"},
            { ShaderDataType::Float4, "a_Color"}
        });
        m_triangleVA->AddVertexBuffer(triangleVB);

        uint32_t triangleIndices[3] = { 0, 1, 2 };
        std::shared_ptr<IndexBuffer> triangleIB;
        triangleIB.reset(IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
        m_triangleVA->SetIndexBuffer(triangleIB);

        // square rendering

        m_squareVA.reset(VertexArray::Create());

        float squareVertices[3 * 4] =
        {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f
        };

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            { ShaderDataType::Float3, "a_Position"}
        });
        m_squareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_squareVA->SetIndexBuffer(squareIB);

        // multi color shader
        
        std::string multiColorShaderVertexSrc = R"(
            #version 330

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_position;
            out vec4 v_color;

            void main()
            {
                v_position = vec3(a_Position);
                v_color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
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

        m_shaderMultiColor.reset(Shader::Create(multiColorShaderVertexSrc, multiColorShaderFragmentSrc));

        // blue color shader
        
        std::string blueShaderVertexSrc = R"(
            #version 330

            layout(location = 0) in vec3 a_Position;

            out vec3 v_position;

            void main()
            {
                v_position = vec3(a_Position);
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string blueShaderFragSrc = R"(
            #version 330

            layout(location = 0) out vec4 color;

            in vec3 v_position;

            void main()
            {
                color = vec4(0.3, 0.2, 0.8, 0.0);
            }
        )";

        m_shaderBlue.reset(Shader::Create(blueShaderVertexSrc, blueShaderFragSrc));
    }

    void EngineApp::Run()
    {
        while(m_isRunning)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_shaderBlue->Bind();
            m_squareVA->Bind();
            glDrawElements(GL_TRIANGLES, m_squareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

            m_shaderMultiColor->Bind();
            m_triangleVA->Bind();
            glDrawElements(GL_TRIANGLES, m_triangleVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_layerStack)
            {
                layer->OnUpdate();
            }

            m_imguiLayer->Begin();
            for (Layer* layer : m_layerStack)
            {
                layer->OnImGuiRender();
            }
            m_imguiLayer->End();

            m_window->Update();
        }
    }

    void EngineApp::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        //ENGINE_INFO(e.ToString());

        dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(EngineApp::OnWindowCloseEvent));

        for(auto it = m_layerStack.end(); it != m_layerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.handled)
            {
                break;
            }
        }
    }

    void EngineApp::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void EngineApp::PushOverlay(Layer* layer)
    {
        m_layerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    bool EngineApp::OnWindowCloseEvent(WindowCloseEvent& e)
    {
        m_isRunning = false;
        return true;
    }
}