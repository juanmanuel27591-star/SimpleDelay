#pragma once

#include "PluginProcessor.h"

class SimpleDelayEditor : public juce::AudioProcessorEditor
{
public:
    explicit SimpleDelayEditor (SimpleDelayProcessor& p);

    void paint (juce::Graphics& g) override;
    void resized() override;

    private:
     SimpleDelayProcessor& delayProcessor;

    juce::Slider timeSlider;
    juce::Slider feedbackSlider;
    juce::Slider mixSlider;
    juce::Label timeLabel;
    juce::Label feedbackLabel;
    juce::Label mixLabel;
    juce::TextButton blipButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDelayEditor)

};