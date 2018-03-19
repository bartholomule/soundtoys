#pragma once

#include "window.hpp"
#include "soundhandler.hpp"

namespace SoundToys
{
	class DSoundWindow : public Window, public SoundHandler
	{
	public:
		DSoundWindow(const std::string& name, const std::string& title);
	};
}