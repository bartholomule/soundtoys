#include "dsoundwindow.hpp"
#include "timer.hpp"

#include <iostream>

int main()
{
	size_t count = 0;
	SoundToys::Timer oneshot(1000, 0, [](bool) { std::cout << "Oneshot timer expired" << std::endl; });
	SoundToys::Timer repeat(1000, 1000, [](bool repeat) { std::cout << "Repeat timer expired (repeat=" << repeat << ")" << std::endl; });
	SoundToys::Timer repeatAutostart(1000, 2000, 
		[&](bool repeat) { 
		++count;
		if (count % 4 == 0) {
			// restart the oneshot every 8 seconds.
			oneshot.start();
		}
		std::cout << "Autostarting repeat timer expired (repeat=" << repeat << ")" << std::endl; 
	}, SoundToys::TimerType::start_now);

	SoundToys::DSoundWindow window("soundtoys-windows", "Sample Window");
	std::cout << "Hello World!" << std::endl;
	window.showNormal();
	oneshot.start();
	repeat.start();
	SoundToys::Window::messageLoop();

	return 0;
}
