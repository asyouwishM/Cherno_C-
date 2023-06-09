
#include "hzpch.h"
#include "ImGuiLayer.h"




#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include "ImGuizmo.h" 

#include "Hazel/Core/Application.h"


namespace Hazel
{

	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer") //初始化 调用父类构造 m_time 初始化与cherno不同 p15	
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}


	void ImGuiLayer::OnAttach() //挂到栈上准备渲染了
	{
		HZ_PROFILE_FUNCTION();



		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		
		//获得imgui的 io流  进行设置
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		//你可以创建一个字体库/用id或枚举来描述调用之类的,随便你
		io.Fonts->AddFontFromFileTTF("Assets/fonts/opensans/OpenSans-Bold.ttf",18.0f); //粗体
		io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/fonts/opensans/OpenSans-Regular.ttf",18.0f); //普通

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
		SetDarkThemeColors();


		// Setup Platform/Renderer backends
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		



		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410"); 
	}

	void ImGuiLayer::OnDetach()
	{
		HZ_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

	}



	void ImGuiLayer::Begin() //OnUpdat() 被拆分为 Begin,ImGuiRender,End	 在渲染数据设置前 调用Begin() ,渲染数据后 调用 end()
	{
		HZ_PROFILE_FUNCTION();


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();

	}
	void ImGuiLayer::End()
	{
		HZ_PROFILE_FUNCTION();

		ImGuiIO& io = ImGui::GetIO();


		Application& app = Application::Get();
		
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(),(float)app.GetWindow().GetHeight());


		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) //如果开启了视口
		{
			GLFWwindow* backup_current_constext = glfwGetCurrentContext();

			ImGui::UpdatePlatformWindows();

			ImGui::RenderPlatformWindowsDefault();

			glfwMakeContextCurrent(backup_current_constext);
		}
	
	} 

	void ImGuiLayer::OnImGuiRender()
	{
		HZ_PROFILE_FUNCTION();

		static bool show = true;



	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		if (m_blockImGuiEvent)
		{

			ImGuiIO& io = ImGui::GetIO();

			event.Handled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureKeyboard;// &io.WantCaptureMouse;//入果事件是Mouse 且 ImGui想要接受事件 那么返回真,停止事件传播
			event.Handled |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;//入果事件是键盘类的 且 ImGui想要监听键盘 ....

			//WantCaptureMouse  的 机制是 如果鼠标悬停或点击了ImGui元素的就会为真(即foucus)/或许是他注释里建议你这么做? 喜喜

		}

		


	}

	void ImGuiLayer::SetDarkThemeColors()
	{
		//这段复制的仓库...艹你 cherno

		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}

	



// 	void ImGuiLayer::OnEvent(Event& e)
// 	{
// 
// 		EventDispatcher diapatcher(e);
// 		switch (e.GetEventType())
// 		{//没必要switch 但是我就要
// 		
// 		case EventType::MouseMoved:
// 			
// 			diapatcher.DisPatch<MouseMoveEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnMouseMoveEvent));
// 			break;
// 		case EventType::MouseButtonPressed :
// 			 
// 			diapatcher.DisPatch<MouseButtonPressedEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnMouseButtonPressedEvent));
// 			break;
// 		case EventType::MouseButtonReleased:
// 			 
// 			diapatcher.DisPatch<MouseButtonReleasedEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnMouseButtonReleasedEvent));
// 			break;
// 		case EventType::MouseScrolled:
// 			 
// 			diapatcher.DisPatch<MouseScorllEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnMouseScorllEvent));
// 			break;
// 		case EventType::KeyPressed:
// 			 
// 			diapatcher.DisPatch<KeyPressedEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnKeyPressedEvent));
// 			break;
// 		case EventType::KeyReleased:
// 			 
// 			diapatcher.DisPatch<KeyReleasedEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnKeyReleasedEvent));
// 			break;
// 		case EventType::WindowResize:
// 			 
// 			diapatcher.DisPatch<WindowsResizeEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnWindowsResizeEvent));
// 			break;
// 		case EventType::KeyTyped:
// 			diapatcher.DisPatch<KeyTypedEvent>(BIND_EVENT_CALLFN(ImGuiLayer::OnKeyTypedEvent));
// 			break;
// 		default:
// 			break;
// 
// 		}
// 
// 
// 	}
// 
// 
// 	bool ImGuiLayer::OnMouseMoveEvent(MouseMoveEvent& e) //模仿Imgui原生的事件回调
// 	{
// 
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.MousePos = ImVec2(e.GetX(), e.GetY());
// 
// 		return false;
// 	}
// 
// 	bool ImGuiLayer::OnMouseScorllEvent(MouseScorllEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.MouseWheelH+=  e.GetXOffset();
// 		io.MouseWheel += e.GetYOffset();
// 
// 
// 		return true;
// 	}
// 
// 	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.MouseDown[e.GetMouseButtonCode()] =true;
// 		return false; //希望继续穿透
// 	}
// 
// 	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.MouseDown[e.GetMouseButtonCode()] = false;
// 		return false; //希望继续穿透
// 	}
// 
// 	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 
// 		//一些关键键被另外保存了(主要是有因为两个)
// 
// 		io.KeysDown[e.GetKeyCode()] = true;
// 		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
// 		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
// 		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
// 		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER]; // windows 键 mac 键
// 		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
// 		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
// 		return true;
// 	}
// 
// 	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.KeysDown[e.GetKeyCode()] = false;
// 		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
// 		return true;
// 	}
// 
// 	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		int keycode = e.GetKeyCode();
// 
// 		if (keycode > 0 && keycode < 0x100000)
// 			io.AddInputCharacter((unsigned int)keycode);//输入文本需要这个,0.0
// 
// 		return false;
// 	}
// 
// 
// 	bool ImGuiLayer::OnWindowsResizeEvent(WindowsResizeEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());//和update重复了
// 		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f); //layer渲染大小:沾满displaysize
// 		glViewport(0, 0, e.GetWidth(), e.GetHeight()); //令gl渲染视口
// 		return true;
// 	}

}