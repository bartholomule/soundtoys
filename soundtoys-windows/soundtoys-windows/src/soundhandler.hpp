#pragma once

#include <dsound.h>

namespace SoundToys
{

	class SoundHandler
	{
	public:
		SoundHandler(HWND handle);
		virtual ~SoundHandler();

		void init(size_t nChannels);
		void cleanup();

	private:
		HWND m_hwnd;
		IDirectSound* m_ds = nullptr;
		IDirectSoundBuffer* m_primaryBuffer = nullptr;
	};
}
