#include "dsoundwindow.hpp"

namespace SoundToys
{
	DSoundWindow::DSoundWindow(const std::string& name, const std::string& title)
		: Window(name, title)
		, SoundHandler(Window::handle())
	{
	}
}