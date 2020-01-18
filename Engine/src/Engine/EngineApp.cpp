#include "EngineApp.h"
#include "Event/WindowEvent.h"
#include "Input.h"

#include <glad/glad.h>

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Engine
{
    EngineApp* EngineApp::m_instance = nullptr;
    RenderAPI Renderer::m_renderAPI = RenderAPI::OpenGL;

    EngineApp::EngineApp()
    {
        if (m_instance != nullptr)
        {
            ENGINE_ERROR("App already exists!");
        }
        else
        {
            m_instance = this;
        }
        
        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(BIND_FN(EngineApp::OnEvent));

        m_imguiLayer = new ImGuiLayer();
        PushOverlay(m_imguiLayer);

        m_vertexArray.reset(VertexArray::Create());

        float vertices[3 * 3] =
        {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        uint32_t indices[3] = { 0, 1, 2 };
        m_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string vertexSource = R"(
            #version 330

            layout(location = 0) in vec3 i_position;
            out vec3 v_position;

            void main()
            {
                v_position = vec3(i_position);
                gl_Position = vec4(i_position, 1.0);
            }
        )";

        std::string fragSource = R"(
            #version 330

            layout(location = 0) out vec4 color;
            in vec3 v_position;

            void main()
            {
                color = vec4(v_position*0.5 + 0.5, 1.0);
            }
        )";

        m_shader.reset(Shader::Create(vertexSource, fragSource));
    }

    void EngineApp::Run()
    {
        while(m_isRunning)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_shader->Bind();
            m_vertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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