#pragma once


#include "Hazel/Layer.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel
{
	class HAZEL_API ImGuiLayer :public Layer
	{ //ui ��
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate() override;
		void OnEvent(Event& e) override;

	private://�����cherno��һ��,������֮���ܸ�ui�����Ӧ
		bool virtual OnMouseMoveEvent(MouseMoveEvent& e);//��Ҫ�ܶ�event��Ӧ ��Ϻܶ�ĵ�����,ģ��imgui���¼��ص������¼�
		bool virtual OnMouseScorllEvent(MouseScorllEvent& e);
		bool virtual OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool virtual OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool virtual OnKeyPressedEvent(KeyPressedEvent& e);
		bool virtual OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool virtual OnWindowsResizeEvent(WindowsResizeEvent& e);
		bool virtual OnKeyTypedEvent(KeyTypedEvent& e);//�����ַ������������


	private:
		float m_time;
	};
};

