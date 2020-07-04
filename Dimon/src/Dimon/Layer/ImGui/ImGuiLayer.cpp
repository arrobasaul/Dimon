#include "dmpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
//#define IMGUI_IMPL_API
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

//#include "Platform/OpenGL/OpenGLRenderer.h"

#include "GLFW/glfw3.h"
#include "Dimon/Application.h"
#include "Dimon/Core.h"

#include "glad/glad.h"
#include "Dimon/Network/ChatServer.h"
namespace Dimon {
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGui")
	{
	}
	ImGuiLayer::~ImGuiLayer()
	{
	}
	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);

		ImGui_ImplOpenGL3_Init("#version 410");
		//auto chat = Ref<ChatServer>(ChatServer::Get());
		//std::thread t((chat));
	}
	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	/*void ImGuiLayer::OnUpdate()
	{
		

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

;		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}*/
	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);

	}
	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(),(float) app.GetWindow().GetHeight());

		//Render
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backupCurrentContex = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContex);
		}
	}
	/*void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispacher(event);

		dispacher.Dispatch<KeyPressedEvent>(DM_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispacher.Dispatch<KeyReleasedEvent>(DM_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispacher.Dispatch<KeyTypedEvent>(DM_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispacher.Dispatch<MouseButtonPressedEvent>(DM_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispacher.Dispatch<MouseButtonReleasedEvent>(DM_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispacher.Dispatch<MouseScrolledEvent>(DM_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispacher.Dispatch<MouseMovedEvent>(DM_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispacher.Dispatch<WindowResizeEvent>(DM_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
		dispacher.Dispatch<KeyPressedEvent>(DM_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));

	}
	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}
	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;
		return false;
	}
	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keyCode = e.GetKeyCode();
		if (keyCode > 0 && keyCode < 0x10000)
			io.AddInputCharacter(keyCode);
		return false;
	}
	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		return false;
	}
	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}
	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(),e.GetY());
		return false;
	}
	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.GetYOffset();
		io.MouseWheelH += e.GetXOffset();
		return false;
	}
	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}*/
}