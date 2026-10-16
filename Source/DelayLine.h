#pragma once

#include <vector>

class DelayLine
{
public:
    void prepare (double sampleRate, double maxDelaySeconds)
    {
        size = (int) (sampleRate * maxDelaySeconds) + 2;
        buffer.assign ((size_t) size, 0.0f);
        writeIndex = 0;
    }

    float read (int delaySamples) const
    {
        if (size == 0)
            return 0.0f;

            if (delaySamples < 1)
                delaySamples = 1;
            if (delaySamples > size - 1)
                delaySamples = size - 1;

            auto readIndex = writeIndex - delaySamples;
            if (readIndex < 0)
                readIndex += size;

                return buffer[(size_t) readIndex];
    }

    void write (float sample)
    {
        if (size == 0)
            return;

            buffer[(size_t) writeIndex] = sample;
            if (++writeIndex >= size)
                writeIndex = 0;
    }

    private:
        std::vector<float> buffer;
        int size = 0;
        int writeIndex = 0;
};