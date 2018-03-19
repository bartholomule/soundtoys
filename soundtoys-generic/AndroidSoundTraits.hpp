#pragma once
#include <cstdint>
#include <cmath>

namespace SoundToys
{
    struct AndroidSoundTraits
    {
        using IntType = int32_t;
        using FloatType = float;
        using PhaseType = double;
        using FrequencyType = double;

        constexpr PhaseType PhaseMinimum = 0;
        constexpr PhaseType PhaseMaximum = 2 * M_PI;
    };
}
