#include "soundhandler.hpp"
#include <stdexcept>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

namespace SoundToys
{
	SoundHandler::SoundHandler(HWND handle) 
		: m_hwnd(handle)
	{
		init(); 
	}

	SoundHandler::~SoundHandler() 
	{ 
		cleanup(); 
	}

	void SoundHandler::init()
	{
		if (DirectSoundCreate(NULL, &m_ds, NULL) != DS_OK) //create direct sound object
		{
			MessageBoxA(m_hwnd, "Could Not Create Direct Sound Object", "Error!", MB_OK);
			throw std::runtime_error("DirectSoundCreate failed");
		}

		//ok, DirectSound Object created, let's take control now...
		if (IDirectSound_SetCooperativeLevel(m_ds, m_hwnd, DSSCL_PRIORITY) != DS_OK)
		{
			MessageBoxA(m_hwnd, "Set Cooperative Level didn't Work!", "BAD!!", MB_OK);
			throw std::runtime_error("Set Cooperative Level didn't Work!");
		}
	}

	void SoundHandler::cleanup()
	{
		if (m_ds != nullptr)
		{
			IDirectSound_Release(m_ds);
		}
		m_ds = nullptr;
	}

}