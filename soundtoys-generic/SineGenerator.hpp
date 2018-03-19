#pragma once

#include "FrequencyGenerator.hpp"
#include <limits>

namespace SoundToys
{
    template <typename Traits>
    class SineGenerator : public FrequencyGenerator<Traits>
    {
    public:
        using Parent = FrequencyGenerator<Traits>;

        SineGenerator(FrequencyType frequencyInHz = 0, uint32_t samplesPerSecond = Traits::DefaultSamplesPerSecond)
            : Parent(frequencyInHz, samplesPerSecond)
        {
            m_phaseMultiplier = calculatePhaseMultiplier();
        }

    protected:
        FloatType generateSampleFloat(PhaseType phase, FloatType amplitude) override
        {
            return Traits::FloatType(sinf(phase * m_phaseMultiplier) * amplitude);
        }

        IntType generateSampleInt(PhaseType phase, FloatType amplitude) override
        {
            return IntType(std::numeric_limits<IntType>::max() * generateSampleFloat(phase, amplitude));
        }

        FloatType calculatePhaseMultiplier() const
        {
            auto phaseSize = Parent::m_maxPhase - Parent::m_minPhase;
            // Unless strange phases are used, this will almost always turn out to be 1.
            m_phaseMultiplier = 2 * M_PI / phaseSize;
        }

    private:
        FloatType m_phaseMultiplier;
    };
}