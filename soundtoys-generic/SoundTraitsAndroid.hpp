#pragma once
#include <cstdint>
#include <cmath>

namespace SoundToys
{
    struct AndroidSoundTraits
    {
        using IntType = int16_t;
        using FloatType = float;
        using PhaseType = double;
        using FrequencyType = double;

		static constexpr IntType DefaultSamplesPerSecond = 44100;
        static constexpr PhaseType PhaseMinimum = 0;
        static constexpr PhaseType PhaseMaximum = 2 * M_PI;
    };
}
