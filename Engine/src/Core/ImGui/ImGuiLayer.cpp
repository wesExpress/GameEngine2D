#include "ImGuiLayer.h"
#include "imgui/imgui.h"
#include "OpenGL/ImGuiOpenGLRenderer.h"

#include "App.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

ImGuiLayer::ImGuiLayer()
:
Layer("ImGuiLayer")
{}

void ImGuiLayer::OnAttach()
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    // using GLFW key codes
    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

    ImGui_ImplOpenGL3_Init("#version 330");

    App& app = App::Get();
    io.DisplaySize.x = app.GetWindow().GetWidth();
    io.DisplaySize.y = app.GetWindow().GetHeight();
    glViewport(0, 0, app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
}

void ImGuiLayer::OnDetach()
{

}

void ImGuiLayer::OnUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    App& app = App::Get();
    io.DisplaySize.x = app.GetWindow().GetWidth();
    io.DisplaySize.y = app.GetWindow().GetHeight();
    glViewport(0, 0, app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    float time = (float)glfwGetTime();
    io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f/60.0f);
    m_time = time; 

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);

    dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_FN(ImGuiLayer::OnMouseButtonPressed));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_FN(ImGuiLayer::OnMouseButtonReleased));
    dispatcher.Dispatch<MouseMovedEvent>(BIND_FN(ImGuiLayer::OnMouseMoved));
    dispatcher.Dispatch<MouseScrolledEvent>(BIND_FN(ImGuiLayer::OnMouseScrolled));
    dispatcher.Dispatch<KeyPressedEvent>(BIND_FN(ImGuiLayer::OnKeyPressed));
    dispatcher.Dispatch<KeyReleasedEvent>(BIND_FN(ImGuiLayer::OnKeyReleased));
    dispatcher.Dispatch<KeyTypedEvent>(BIND_FN(ImGuiLayer::OnKeyTyped));
    dispatcher.Dispatch<WindowResizeEvent>(BIND_FN(ImGuiLayer::OnWindowResize));
}

bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();

    io.MousePos.x = (float)e.GetMouseX();
    io.MousePos.y = (float)e.GetMouseY();

    LOG_WARN("ImGui MouseMovedEvent: ({0}, {1})", io.MousePos.x, io.MousePos.y);

    return false;
}

bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();

    io.MouseWheelH += (float)e.GetXDiff();
    io.MouseWheel += (float)e.GetYDiff();

    LOG_WARN("ImGui MouseScrolledEvent: ({0}, {1})", io.MouseWheelH, io.MouseWheel);

    return false;
}

bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();

    io.MouseDown[e.GetButton()] = true;

    LOG_WARN("ImGui MouseButtonPressedEvent: {0}", e.GetButton());

    return false;
}

bool ImGuiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();

    io.MouseDown[e.GetButton()] = false;

    LOG_WARN("ImGui MouseButtonReleasedEvent: {0}", e.GetButton());

    return false;
}

bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();

    io.KeysDown[e.GetKeyCode()] = true;

    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

    LOG_WARN("ImGui MouseButtonPressedEvent: {0}", e.GetKeyCode());

    return false;
}

bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();

    io.KeysDown[e.GetKeyCode()] = false;

    LOG_WARN("ImGui MouseButtonReleasedEvent: {0}", e.GetKeyCode());

    return false;
}

bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();

    io.AddInputCharacter(e.GetKeyCode());

    LOG_WARN("ImGui KeyTypedEvent: {0}", e.GetKeyCode());

    return false;
}

bool ImGuiLayer::OnWindowResize(WindowResizeEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();

    io.DisplaySize.x = (float)e.GetWidth();
    io.DisplaySize.y = (float)e.GetHeight();

    io.DisplayFramebufferScale.x = 1.0f;
    io.DisplayFramebufferScale.y = 1.0f;
    glViewport(0, 0, e.GetWidth(), e.GetHeight());

    LOG_WARN("ImGui WindowResizeEvent");

    return false;
}