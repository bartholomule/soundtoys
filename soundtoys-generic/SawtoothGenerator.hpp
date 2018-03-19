#pragma once

#include "FrequencyGenerator.hpp"
#include <limits>

namespace SoundToys
{
    enum class SawtoothType { normal, reversed };

    template <typename Traits>
    class SawtoothGenerator : public FrequencyGenerator<Traits>
    {
    public:
        using Parent = FrequencyGenerator<Traits>;

        SawtoothGenerator(SawtoothType type = SawtoothType::normal, FrequencyType frequencyInHz = 0, uint32_t samplesPerSecond = Traits::DefaultSamplesPerSecond)
            : Parent(frequencyInHz, samplesPerSecond)
            , m_type(type)
        {
            auto phaseWidth = Parent::m_maxPhase - Parent::m_minPhase;
            m_dcOffset = 1;
            m_phaseMultiplier = FloatType(2.0) / FloatType(phaseWidth);
        }

    protected:
        FloatType generateSampleFloat(PhaseType phase, FloatType amplitude) override
        {
            // This is doubled (in the multipler) and DC shifted down so that it covers the full
            // range instead of just being a halfwave sawtooth.
            FloatType result = amplitude * (phase * m_phaseMultiplier - m_dcOffset);
            if( m_type == SawtoothType::reversed)
            {
                return amplitude - result;
            }
            return result;
        }

        IntType generateSampleInt(PhaseType phase, FloatType amplitude) override
        {
            return IntType(std::numeric_limits<IntType>::max() * generateSampleFloat(phase, amplitude));
        }

    private:
        SawtoothType m_type;
        // 2 / phase width
        FloatType m_phaseMultiplier;
        // DC shift to allow full range of the signal.
        FloatType m_dcOffset;
    };
}