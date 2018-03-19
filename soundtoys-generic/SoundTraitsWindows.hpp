#pragma once
#include <cstdint>
#define _USE_MATH_DEFINES
#include <cmath>

namespace SoundToys
{
    struct WindowsSoundTraits
    {
        using IntType = int16_t;
        using FloatType = float;
        using PhaseType = double;
        using FrequencyType = double;

		static constexpr size_t DefaultSamplesPerSecond = 44100;
		static constexpr size_t DefaultBitsPerSample = 16;
        static constexpr PhaseType PhaseMinimum = 0;
        static constexpr PhaseType PhaseMaximum = 2 * M_PI;
    };
}
