#pragma once
#include "core.h"

namespace Hazel {


	class HAZEL_API Application
	{

	public:
		Application();
		virtual ~Application();
		void Run();
	};
	//To be definde in CLIENT һ���ӿ�,�ڿͻ���ʵ��
	Hazel::Application* CreateApplication();
}