#include "EngineApp.h"
#include "Event/WindowEvent.h"
#include "Input.h"

#include <glad/glad.h>

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Engine
{
    static GLenum ShaderTypeToOpenGLType(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4: return GL_INT;

            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4: return GL_FLOAT;

            case ShaderDataType::Bool: return GL_BOOL;

            default: return 0;
        }
    }

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

        float vertices[3 * 7] =
        {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.3f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.3f, 0.2f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.7f, 0.8f, 0.2f, 1.0f
        };

        m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        {
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position"},
                { ShaderDataType::Float4, "a_Color"}
            };
            m_vertexBuffer->SetLayout(layout);
        }

        const auto& layout = m_vertexBuffer->GetLayout();
        uint32_t index = 0;
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index, 
                element.GetElementCount(), 
                ShaderTypeToOpenGLType(element.type), 
                element.normalized ? GL_TRUE : GL_FALSE, 
                layout.GetStride(), 
                (const void *)element.offset);
            index++;
        }

        uint32_t indices[3] = { 0, 1, 2 };
        m_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string vertexSource = R"(
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

        std::string fragSource = R"(
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