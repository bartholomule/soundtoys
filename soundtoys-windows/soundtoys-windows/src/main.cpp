#include "DSoundWindow.hpp"

#include <iostream>

int main()
{
	SoundToys::DSoundWindow window("soundtoys-windows", "Sample Window");
	std::cout << "Hello World!" << std::endl;
	window.showNormal();
	SoundToys::Window::messageLoop();

	return 0;
}
