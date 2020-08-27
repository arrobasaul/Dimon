#include "EditorLayer.h"
#include "ImGui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"
#include "Dimon/Debug/Intrumentor.h"
namespace Dimon {


	static const uint32_t s_MapWidth = 24;
	static const char* s_MapTiles =
		"SSSSSSSSSSSSSSSSSSSSSSSS"
		"SSWWWWWWWWWWWWWWWWWWWWSS"
		"SSWWWWWWWWWWWWWWWWWWWWSS"
		"SSWSSSSSSTSSSSSSSSSSSWSS"
		"SSWSSTWWWTSSSSSTSSTSSWSS"
		"SSWSSTWWWTSSSSTSSSSSSWSS"
		"SSWSSSSWSSSSSSSSSTTSSWSS"
		"SSWSSTSTSSSSSTSSSTTSSWSS"
		"SSWSSSSSSSSSSSSTSSSSSWSS"
		"SSWWWWWWPWWWWWWPWWWWWWSS"
		"SSSSSSSSSSSSSSSSSSSSSSSS"
		"SSSSSSSSSSSSSSSSSSSSSSSS"
		;

	EditorLayer::EditorLayer()
		: Layer("Minecraf"), m_CameraController(1920.0f / 1440.0f)
	{
	}
	void EditorLayer::OnAttach()
	{
		//auto textureShader = m_ShaderLibrary.Load("TextShaderImage", "Resources/Shaders/TextShader.vert", "Resources/Shaders/TextShader.frag");
		m_DimonTexture = Dimon::Texture2D::Create("Resources/Texture/Checkerboard.png");


		Dimon::FramebufferSpesification spec;
		spec.Width = 1280;
		spec.Height = 720;

		m_FrameBuffer = Dimon::FrameBuffer::Create(spec);
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Dimon::TimeStep timeStep)
	{
		DM_PROFILE_FUNCTION();
		{
			DM_PROFILE_SCOPE("m_CameraController.OnUpdate");
			m_CameraController.OnUpdate(timeStep);
		}
		Dimon::Renderer2D::ResetStat();
		{
			DM_PROFILE_SCOPE("Sandbox2D::Render");
			m_FrameBuffer->Bind();
			Dimon::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			Dimon::RendererCommand::Clear();
		}
		{


#if 1
			DM_PROFILE_SCOPE("Sandbox2D::Draw");
			Dimon::Renderer2D::BeginScene(m_CameraController.GetCamera());

			Dimon::Renderer2D::DrawRotateQuad(glm::vec2({ 1.0f,0.0f }), glm::vec2({ 0.8f,0.8f }), -45.0f, m_SquereColor);

			Dimon::Renderer2D::DrawQuad(glm::vec2({ -1.0f,0.0f }), glm::vec2({ 0.8f,0.8f }), m_SquereColor);
			Dimon::Renderer2D::DrawQuad(glm::vec2({ 0.5f,-0.5f }), glm::vec2({ 0.5f,0.75f }), m_SquereColor);
			//Dimon::Renderer2D::DrawQuad(glm::vec2({ 0.0f,-0.5f }), glm::vec2({ 0.5f,0.75f }), { 0.1f, 1.0f, 0.1f, 1.0f });
			Dimon::Renderer2D::DrawRotateQuad(glm::vec3({ -2.0f, 0.0f,0.0f }), glm::vec2({ 1.0f,1.0f }), -45.0f, m_DimonTexture, 20.0f);
			Dimon::Renderer2D::EndScene();

			Dimon::Renderer2D::BeginScene(m_CameraController.GetCamera());
			for (float y = -0.5f; y < 5.0f; y += 0.5f)
			{
				for (float x = -0.5f; x < 5.0f; x += 0.5f)
				{
					Dimon::Renderer2D::DrawRotateQuad(glm::vec2({ x,y }), glm::vec2({ 0.45f,0.45f }), 45, m_SquereColor);
					//Dimon::Renderer2D::DrawQuad(glm::vec2({ x,y }), glm::vec2({ 0.45f,0.45f }), { 1.0f, 0.1f, 0.1f, 1.0f });
				}
			}
			Dimon::Renderer2D::EndScene();
			m_FrameBuffer->UnBind();
#endif
#if 0
			Dimon::Renderer2D::BeginScene(m_CameraController.GetCamera());

			//Dimon::Renderer2D::DrawQuad(glm::vec3({ 0.0f, 0.0f,-0.1f }), glm::vec2({ 20.0f, 20.0f }), m_DimonTexture, 20.0f);
			//Dimon::Renderer2D::DrawQuad(glm::vec3({ 0.0f, 0.0f, 0.0f }), glm::vec2({ 10.0f, 10.0f }), m_TextureStrait, 1.0f);

			for (uint32_t y = 0; y < m_MapHeight; y++)
			{
				for (uint32_t x = 0; x < m_MapWidth; x++)
				{
					char tile = s_MapTiles[x + y * m_MapWidth];
					Dimon::Ref<Dimon::SubTexture2D> subTexture;
					if (s_TextureMap.find(tile) != s_TextureMap.end())
						subTexture = s_TextureMap[tile];
					else
						subTexture = m_TextureStrait;

					Dimon::Renderer2D::DrawQuad(glm::vec3({ x - m_MapWidth / 2.0f, m_MapWidth - y - m_MapWidth / 2.0f, 0.5f }), glm::vec2({ 1.0f, 1.0f }), subTexture, 1.0f);
				}
			}
			Dimon::Renderer2D::EndScene();
			m_FrameBuffer->UnBind();
#endif
		}
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool opt_fullscreen_persistant = true, DockSpaceOpen = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &DockSpaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Docking"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 dockspace_flags ^= ImGuiDockNodeFlags_NoSplit;
				if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0))     dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
				if (ImGui::MenuItem("Exit")) Dimon::Application::Get().Close();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
		ImGui::Begin("Setting");
		auto stats = Dimon::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Counts: %d", stats.QuadCount);
		ImGui::Text("Index Counts: %d", stats.GetTotalIndexCount());
		ImGui::Text("Vertex Counts: %d", stats.GetTotalVertexCount());

		ImGui::ColorEdit4("Color", glm::value_ptr(m_SquereColor));

		ImGui::End();

		//ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });

		ImGui::Begin("Editor");
		ImVec2 ViewPortPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViePortSize != *((glm::vec2*) & ViewPortPanelSize)) {
			m_FrameBuffer->Resize((uint32_t)ViewPortPanelSize.x, (uint32_t)ViewPortPanelSize.y);
			m_ViePortSize = { ViewPortPanelSize.x, ViewPortPanelSize.y };

			m_CameraController.OnResize(ViewPortPanelSize.x, ViewPortPanelSize.y);
		}
		DM_CORE_WARM("view port {0} {1}", ViewPortPanelSize.x, ViewPortPanelSize.y);
		uint32_t textureId = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureId, ImVec2{ ViewPortPanelSize.x, ViewPortPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();

		ImGui::End();

	}

	void EditorLayer::OnEvent(Dimon::Event& event)
	{
		m_CameraController.OnEvent(event);
	}
}