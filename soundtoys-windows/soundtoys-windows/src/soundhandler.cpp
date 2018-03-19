#include "soundhandler.hpp"
#include "SoundTraitsWindows.hpp"
#include <stdexcept>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

namespace SoundToys
{
	SoundHandler::SoundHandler(HWND handle) 
		: m_hwnd(handle)
	{
		init(2); 
	}

	SoundHandler::~SoundHandler() 
	{ 
		cleanup(); 
	}

	void SoundHandler::init(size_t nChannels)
	{
		if (DirectSoundCreate(NULL, &m_ds, NULL) != DS_OK) //create direct sound object
		{
			MessageBoxA(m_hwnd, "DirectSoundCreate failed", "Error", MB_OK);
			throw std::runtime_error("DirectSoundCreate failed");
		}

		//ok, DirectSound Object created, let's take control now...
		if (IDirectSound_SetCooperativeLevel(m_ds, m_hwnd, DSSCL_PRIORITY) != DS_OK)
		{
			MessageBoxA(m_hwnd, "Failed call to SetCooperativeLevel", "ERROR", MB_OK);
			throw std::runtime_error("Failed call to IDirectSound_SetCooperativeLevel");
		}

		DSBUFFERDESC bufferDesc;
		bufferDesc.dwSize = sizeof(DSBUFFERDESC);
		bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
		bufferDesc.dwBufferBytes = 0;
		bufferDesc.dwReserved = 0;
		bufferDesc.lpwfxFormat = nullptr;
		bufferDesc.guid3DAlgorithm = GUID_NULL;

		if(FAILED(m_ds->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL)))
		{
			throw std::runtime_error("Failed to create primary sound buffer");
		}

		WAVEFORMATEX waveFormat;
		waveFormat.wFormatTag = WAVE_FORMAT_PCM;
		waveFormat.nSamplesPerSec = DWORD(WindowsSoundTraits::DefaultSamplesPerSecond);
		waveFormat.wBitsPerSample = WindowsSoundTraits::DefaultBitsPerSample;
		waveFormat.nChannels = nChannels;
		waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
		waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
		waveFormat.cbSize = 0;

		// Set the primary buffer to be the wave format specified.
		if (FAILED(m_primaryBuffer->SetFormat(&waveFormat)))
		{
			throw std::runtime_error("Failed to set wave format.");
		}

	}

	void SoundHandler::cleanup()
	{
		if (m_primaryBuffer)
		{
			m_primaryBuffer->Release();
			m_primaryBuffer = nullptr;
		}

		if (m_ds != nullptr)
		{
			IDirectSound_Release(m_ds);
		}
		m_ds = nullptr;
	}
}