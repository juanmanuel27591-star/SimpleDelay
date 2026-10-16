#pragma once

#include <atomic>
#include <juce_audio_utils/juce_audio_utils.h>
#include "TestSound.h"
#include "DelayLine.h"

class SimpleDelayProcessor : public juce::AudioProcessor
{
public:
    SimpleDelayProcessor();

    void prepareToPlay (double sr, int blockSize) override;
    void releaseResources() override;
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;
    bool acceptsMidi() const override; 
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& name) override;

    void getStateInformation (juce::MemoryBlock& data) override;
    void setStateInformation (const void* data, int size) override;

    std::atomic<float> timeMs { 300.0f };
    std::atomic<float> feedback { 0.4f };
    std::atomic<float> mix { 0.5f };

    TestSound testSound;

    private:
        DelayLine delays[2];
        double currentSampleRate = 44100.0;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDelayProcessor)
};