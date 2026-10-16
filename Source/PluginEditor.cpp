#include "PluginEditor.h"

SimpleDelayEditor::SimpleDelayEditor (SimpleDelayProcessor& p)
: AudioProcessorEditor (p), delayProcessor (p)
{
    timeSlider.setRange (1.0, 1000.0, 1.0);
    timeSlider.setTextValueSuffix (" ms");
    timeSlider.setValue (delayProcessor.timeMs.load(), juce::dontSendNotification);
    timeSlider.onValueChange = [this]
{
    delayProcessor.timeMs.store ((float) timeSlider.getValue());
};
    addAndMakeVisible (timeSlider);
    timeLabel.setText ("Time", juce::dontSendNotification);
    timeLabel.attachToComponent (&timeSlider, true);

    feedbackSlider.setRange (0.0, 0.95, 0.01);
    feedbackSlider.setValue (delayProcessor.feedback.load(), juce::dontSendNotification);
    feedbackSlider.onValueChange = [this]
    {
        delayProcessor.feedback.store ((float) feedbackSlider.getValue());
    };
    addAndMakeVisible (feedbackSlider);
    feedbackLabel.setText ("Feedback", juce::dontSendNotification);
    feedbackLabel.attachToComponent (&feedbackSlider, true);

    mixSlider.setRange (0.0, 100.0, 1.0);
    mixSlider.setTextValueSuffix (" %");
    mixSlider.setValue (delayProcessor.mix.load() * 100.0, juce::dontSendNotification);
    mixSlider.onValueChange = [this]
    {
        delayProcessor.mix.store ((float) mixSlider.getValue() / 100.0f);
    };
    addAndMakeVisible (mixSlider);
    mixLabel.setText ("Mix", juce::dontSendNotification);
    mixLabel.attachToComponent (&mixSlider, true);

    blipButton.setButtonText ("Play blip");
    blipButton.onClick = [this]
    {
        delayProcessor.testSound.trigger();
    };
    addAndMakeVisible (blipButton);

    setSize (420, 240);
}

void SimpleDelayEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void SimpleDelayEditor::resized()
{
    auto area = getLocalBounds().reduced (20);
    auto buttonArea = area.removeFromBottom (36);
    area.removeFromLeft (70);
    auto rowHeight = area.getHeight() / 3;

    timeSlider.setBounds (area.removeFromTop (rowHeight));
    feedbackSlider.setBounds (area.removeFromTop (rowHeight));
    mixSlider.setBounds (area);
    blipButton.setBounds (buttonArea);
}