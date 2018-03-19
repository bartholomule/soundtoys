#pragma once

#include <dsound.h>

namespace SoundToys
{

	class SoundHandler
	{
	public:
		SoundHandler(HWND handle);
		virtual ~SoundHandler();

		void init();
		void cleanup();

	private:
		HWND m_hwnd;
		LPDIRECTSOUND m_ds = nullptr;
	};
}
