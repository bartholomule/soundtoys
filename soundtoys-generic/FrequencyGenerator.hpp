#pragma once

#include "SoundGenerator.hpp"
#include <math.h>

namespace SoundToys
{
    template<typename Traits>
    class FrequencyGenerator : public SoundGenerator<Traits>
    {
    public:
        using Parent = SoundGenerator<Traits>;
        using IntType = Traits::IntType;
        using FloatType = Traits::FloatType;
        using PhaseType = Traits::PhaseType;
        using FrequencyType = Traits::FrequencyType;

        FrequencyGenerator(FrequencyType frequencyInHz = 0, uint32_t samplesPerSecond = Traits::DefaultSamplesPerSecond)
            : Parent(samplesPerSecond)
            , m_frequencyInHz(frequencyInHz)
        {
            m_phaseIncrement = calculatePhaseIncrement(m_frequencyInHz);
        }

        void setSampleRate(uint32_t sampleRate) override
        {
            Parent::setSampleRate(sampleRate);
            m_phaseIncrement = calculatePhaseIncrement(m_frequencyInHz);
        }

        virtual void setFrequency(FrequencyType frequencyInHz)
        {
            m_frequencyInHz = frequencyInHz;
            m_phaseIncrement = calculatePhaseIncrement(m_frequencyInHz);
        }

        virtual void setAmplitude(FloatType amplitude) { m_amplitude = amplitude; }

        void renderInt(IntType* buffer, size_t channelStride, size_t numSamples) override
        {
            IntType* location = buffer;
            for (size_t i = 0; i < numSamples; i++)
            {
                *location = generateSampleInt(m_phase, m_amplitude);
                location += channelStride;
                m_phase = advancePhaseForSample(m_phase);
            }
        }

        void renderFloat(FloatType* buffer, size_t channelStride, size_t numSamples) override
        {
            IntType* location = buffer;
            for (size_t i = 0; i < numSamples; i++)
            {
                *location = generateSampleFloat(m_phase, m_amplitude);
                location += channelStride;
                m_phase = advancePhaseForSample(m_phase);
            }
        }

    protected:
        virtual FloatType generateSampleFloat(PhaseType phase, FloatType amplitude) { return 0; }
        virtual IntType generateSampleInt(PhaseType phase, FloatType amplitude) { return 0; }

        virtual PhaseType advancePhaseForSample(PhaseType phase)
        {
            phase += m_phaseIncrement;
            while( phase >= m_maxPhase)
            {
                phase -= (m_maxPhase - m_minPhase);
            }
            return phase;
        }

        PhaseType calculatePhaseIncrement(FrequencyType frequencyInHz) const
        {
            PhaseType phaseSize = m_maxPhase - m_minPhase;
            return (frequencyInHz * phaseSize) / m_samplesPerSecond;
        }

        PhaseType m_minPhase = Traits::PhaseMinimum;
        PhaseType m_maxPhase = Traits::PhaseMaximum;

    private:
        FrequencyType m_frequencyInHz;
        PhaseType m_phase = Traits::PhaseMinimum;
        PhaseType m_phaseIncrement = 0;
        FloatType m_amplitude = 1;
    };
}