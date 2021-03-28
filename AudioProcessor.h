#ifndef AUDIO_PROCESSOR_
#define AUDIO_PROCESSOR_
#include <vector>
#include <iostream>
#include <math.h>
#include<stdexcept>
class AudioProcessor
{
    public:
        std::vector<short> Compress(const std::vector<short> & audio, short threshold, float rate);
        std::vector<short> CutOutSilence(const std::vector<short> & audio, short level, int silenceLength);
        std::vector<short> StretchTwice(const std::vector<short> & audio);
        std::vector<short> Normalize(const std::vector<short> & audio, short normalizeTarget);
};
#endif