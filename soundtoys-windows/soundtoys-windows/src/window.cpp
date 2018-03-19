#include "window.hpp"
#include <iostream>

namespace SoundToys
{
	Window::Window(const std::string name, const std::string& text, HINSTANCE hinstance)
		: m_name(name)
		, m_title(text)
	{
		create(hinstance);
	}

	Window::~Window()
	{
		destroy();
	}

	Window::operator bool() const 
	{
		return m_hwnd != nullptr; 
	}

	HWND Window::handle() const 
	{
		return m_hwnd; 
	}

	void Window::create(HINSTANCE hinstance)
	{
		WNDCLASSA wc = {};
		wc.lpfnWndProc = StaticWindowCallback;
		wc.hInstance = hinstance;
		wc.lpszClassName = m_name.c_str();
		RegisterClass(&wc);

		// Create the window.
		m_hwnd = CreateWindowExA(
			0,                   // Optional window styles.
			m_name.c_str(),      // Window class
			m_title.c_str(),     // Window text
			WS_OVERLAPPEDWINDOW, // Window style

								 // Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

			NULL,       // Parent window    
			NULL,       // Menu
			hinstance,  // Instance handle
			this        // Additional application data (pointer to self)
		);

		if (m_hwnd == nullptr)
		{
			throw std::runtime_error("Failed creating window");
		}
	}

	void Window::showNormal()
	{
		show(SW_SHOW); 
	}

	void Window::hide()
	{
		show(SW_HIDE); 
	}

	void Window::destroy()
	{
		if (m_hwnd) 
		{
			DestroyWindow(m_hwnd);
			m_hwnd = nullptr;
		}
	}

	void Window::quit()
	{
		PostQuitMessage(0);
	}

	void Window::paint()
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(m_hwnd, &ps);
	}

	void Window::buttonDown(int x, int y)
	{
		std::cout << "Button pressed at (" << x << ", " << y << ")" << std::endl;
	}

	void Window::buttonUp(int x, int y)
	{
		std::cout << "Button released at (" << x << ", " << y << ")" << std::endl;
	}


	LRESULT CALLBACK Window::StaticWindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Window *pThis;

		if (uMsg == WM_NCCREATE)
		{
			pThis = static_cast<Window*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

			SetLastError(0);
			if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
			{
				if (GetLastError() != 0)
					return FALSE;
			}
		}
		else
		{
			pThis = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		}

		switch (uMsg)
		{
		case WM_DESTROY:
			pThis->quit();
			return 0;
		case WM_PAINT:
			pThis->paint();
			return 0;
		case WM_LBUTTONDOWN:
			pThis->buttonDown(int(LOWORD(lParam)), int(HIWORD(lParam)));
			return 0;
		case WM_LBUTTONUP:
			pThis->buttonUp(int(LOWORD(lParam)), int(HIWORD(lParam)));
			return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	int Window::messageLoop()
	{
		MSG msg = {};
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return 0;
	}

	void Window::show(int nCmdShow)
	{
		ShowWindow(m_hwnd, nCmdShow);
	}
}