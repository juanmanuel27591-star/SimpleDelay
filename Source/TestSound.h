#pragma

#include <atomic>
#include <cmath>

struct TestSound
{
    void prepare (double newSampleRate)
    {
        sampleRate = newSampleRate;
        lengthInSamples = (int) (0.15 * sampleRate);
    }

    void trigger()
    {
        triggered.store (true);
    }

    float getNextSample()
    {
        if (triggered.exchange (false))
        position = 0;

        if (position >=lengthInSamples)
            return 0.0f;

        auto t = (double) position / sampleRate;
        auto tone = std::sin (2.0 * 3.141592653589793 * 880.0 * t);

        auto envelope = 1.0 - (double) position
                / (double) lengthInSamples;

        ++position;
        return (float) (tone * envelope * 0.5);
    }

    private: 
        double sampleRate = 44100.0;
        int lengthInSamples = 0;
        int position = 0;
        std::atomic<bool> triggered { false };
};