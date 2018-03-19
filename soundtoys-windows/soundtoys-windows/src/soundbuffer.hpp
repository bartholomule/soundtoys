#pragma once

#include <dsound.h>
#include <functional>

namespace SoundToys
{
	class SoundHandler;

	class SoundBuffer
	{
	public:
		SoundBuffer() = default;
		~SoundBuffer();
		SoundBuffer(SoundBuffer&& old);
		SoundBuffer& operator=(SoundBuffer&& old);
		// Move-only.
		SoundBuffer(const SoundBuffer&) = delete;
		SoundBuffer& operator=(const SoundBuffer&) = delete;


		size_t getWriteAvailable() const;
		size_t bufferSize() const;

		using DataProducer = std::function<size_t(BYTE* data, size_t amount)>;
		// Produce data from the supplied producer and write it to the internal buffer.  The producer may be called more than once.
		size_t writeData(DataProducer producer, size_t estimatedSize);

	protected:
		SoundBuffer(IDirectSound* ds, size_t bufferBytes, WAVEFORMATEX* format);
		friend class SoundHandler;

	private:
		void setup(size_t bufferBytes, WAVEFORMATEX* format);
		void teardown();

		IDirectSound* m_ds = nullptr;
		IDirectSoundBuffer* m_buffer = nullptr;
		DSBUFFERDESC m_bufferDesc;
		DWORD m_writeCursor = 0;
	};
}