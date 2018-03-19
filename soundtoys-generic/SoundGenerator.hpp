#pragma once

#include <cstdint>

namespace SoundToys
{
    template <typename Traits>
    class SoundGenerator
    {
    public:
        SoundGenerator(uint32_t samplesPerSecond = Traits::DefaultSamplesPerSecond) : m_samplesPerSecond(samplesPerSecond) { }
        virtual ~SoundGenerator() = default;

        virtual void setSampleRate(uint32_t sampleRate) { m_samplesPerSecond = sampleRate; }
        uint32_t getSampleRate() const { return m_samplesPerSecond; }

        virtual void renderInt(Traits::IntType* buffer, size_t channelStride, size_t numSamples) = 0;
        virtual void renderFloat(Traits::FloatType* buffer, size_t channelStride, size_t numSamples) = 0;

    protected:
        uint32_t m_samplesPerSecond; // Hz
    };
}