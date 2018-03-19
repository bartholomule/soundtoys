#pragma once

#include <Windows.h>
#include <string>

namespace SoundToys
{
	class Window
	{
	public:
		Window(const std::string name, const std::string& text, HINSTANCE hinstance = nullptr);
		virtual ~Window();
		operator bool() const;
		HWND handle() const;
		void create(HINSTANCE hinstance);
		
		void showNormal();
		void hide();
		void destroy();
		void quit();
		void paint();
		
		void buttonDown(int x, int y);
		void buttonUp(int x, int y);
		static LRESULT CALLBACK StaticWindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static int messageLoop();

	protected:
		void show(int nCmdShow);

	private:
		std::string m_name;
		std::string m_title;
		HWND m_hwnd = nullptr;
	};

}