
#include "Event.h"
#include "Hazel/Core/KeyCodes.h"
#include "hzpch.h"
namespace Hazel
{

	class  KeyEvent:public Event  //类内写的函数定义会被视为inline
	{
	public:
		
		inline Key GetKeyCode() const{return (Key)m_keycode;}
		
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard ) // | 或运算赋
	protected://允许子类访问
		KeyEvent(int Event):m_keycode(Event){} //是内联的
		int m_keycode;
	};

	class  KeyPressedEvent :public KeyEvent //按下按键 在按一次和长按间需要缓冲时间把这两件事区分开
	{
		

	public:
		inline int GetRepeatcount() const { return m_repeatCount; }

		KeyPressedEvent(int keycode, int repeatc)
			:KeyEvent(keycode), m_repeatCount(repeatc) {}; //调用基类构造函数
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keycode << "(" << m_repeatCount << "repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);
	private:
		int m_repeatCount;
	};

	class  KeyReleasedEvent :public KeyEvent //按下按键 在按一次和长按间需要缓冲时间把这两件事区分开
	{


	public:

		KeyReleasedEvent(int keycode)
			:KeyEvent(keycode) {}; //调用基类构造函数

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);

	};

	class  KeyTypedEvent :public KeyEvent //按下按键 只知道按了哪个键
	{


	public:

		KeyTypedEvent(int keycode)
			:KeyEvent(keycode) {}; //调用基类构造函数

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);

	};



}