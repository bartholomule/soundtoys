#include "soundbuffer.hpp"
#include "scopeexit.hpp"
#include "memory.hpp"
#include <stdexcept>
#include <algorithm>

#undef min

namespace SoundToys
{
	SoundBuffer::SoundBuffer(IDirectSound* ds, size_t bufferBytes, WAVEFORMATEX* format)
		: m_ds(ds)
	{
		setup(bufferBytes, format);
	}

	SoundBuffer::SoundBuffer(SoundBuffer&& old)
	{
		safe_memcpy(m_bufferDesc, old.m_bufferDesc);
		std::swap(m_ds, old.m_ds);
		std::swap(m_buffer, old.m_buffer);
		m_writeCursor = old.m_writeCursor;
	}

	SoundBuffer& SoundBuffer::operator=(SoundBuffer&& old)
	{
		teardown();
		m_ds = nullptr;
		safe_memcpy(m_bufferDesc, old.m_bufferDesc);
		std::swap(m_ds, old.m_ds);
		std::swap(m_buffer, old.m_buffer);
		m_writeCursor = old.m_writeCursor;
		return *this;
	}

	SoundBuffer::~SoundBuffer()
	{
		teardown();
		m_ds = nullptr;
	}

	void SoundBuffer::setup(size_t bufferBytes, WAVEFORMATEX* format)
	{
		safe_memzero(m_bufferDesc);
		m_bufferDesc.dwSize = sizeof(DSBUFFERDESC);
		m_bufferDesc.dwBufferBytes = DWORD(bufferBytes);
		m_bufferDesc.lpwfxFormat = format;
		HRESULT hr = m_ds->CreateSoundBuffer(&m_bufferDesc, &m_buffer, nullptr);
		if (!SUCCEEDED(hr))
		{
			throw std::runtime_error("Failed creating sound buffer");
		}
	}

	void SoundBuffer::teardown()
	{
		if (m_buffer)
		{
			m_buffer->Release();
			// Clear some junk to be safe.
			m_buffer = nullptr;
			safe_memzero(m_bufferDesc);
			m_writeCursor = 0;
		}
	}

	size_t SoundBuffer::bufferSize() const
	{
		return size_t(m_bufferDesc.dwSize);
	}

	size_t SoundBuffer::getWriteAvailable() const
	{
		size_t result = 0;

		// This only gets the play cursor and not the write cursor because lots of people 
		// have reported problems where the write cursor is not accurate due to buffering.
		// We instead manitain our own write cursor.
		DWORD playCursor = 0;
		if (m_buffer->GetCurrentPosition(&playCursor, nullptr) != DS_OK)
		{
			result = 0;
		}
		else if (m_writeCursor <= playCursor)
		{
			result = playCursor - m_writeCursor;
		}
		else // wrapped around the circular buffer.
		{
			result = bufferSize() - m_writeCursor + playCursor;
		}

		return result;
	}

	size_t SoundBuffer::writeData(SoundBuffer::DataProducer producer, size_t estimatedSize)
	{
		DWORD size = std::min(getWriteAvailable(), estimatedSize);
		BYTE* buf1 = nullptr;
		DWORD size1 = 0;
		DWORD written1 = 0;
		BYTE* buf2 = nullptr;
		DWORD size2 = 0;
		DWORD written2 = 0;
		HRESULT hr = m_buffer->Lock(m_writeCursor, size, (void**)&buf1, &size1, (void**)&buf2, &size2, 0);

		// Ensure the unlocking happens if an exception is thrown in the producer.
		ScopeExit bufferRelease = [&]() {
			if (SUCCEEDED(hr))
			{
				m_buffer->Unlock(buf1, written1, buf2, written2);
			}
		};

		if (SUCCEEDED(hr))
		{
			written1 = producer(buf1, size1);
			if (buf2 != nullptr && written1 == size1)
			{
				written2 = producer(buf2, size2);
			}
			m_writeCursor = (m_writeCursor + written1 + written2) % bufferSize();
			return size_t(written1) + size_t(written2);
		}
		return 0;
	}
}