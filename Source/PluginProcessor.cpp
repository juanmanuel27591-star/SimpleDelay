#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleDelayProcessor::SimpleDelayProcessor()
: AudioProcessor (BusesProperties()
.withInput ("Input", juce::AudioChannelSet::stereo(), true)
.withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
}

void SimpleDelayProcessor::prepareToPlay (double sampleRate, int)
{
    currentSampleRate = sampleRate;
    testSound.prepare (sampleRate);
    delays[0].prepare (sampleRate, 1.0);
    delays[1].prepare (sampleRate, 1.0);
}

void SimpleDelayProcessor::releaseResources()
{
}

bool SimpleDelayProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const 
{
    auto out = layouts.getMainOutputChannelSet();

    if (out != juce::AudioChannelSet::mono()
    && out != juce::AudioChannelSet::stereo()) 
    return false;

    return out == layouts.getMainInputChannelSet();
}

void SimpleDelayProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    auto numSamples = buffer.getNumSamples();
    auto numChannels = buffer.getNumChannels();

    auto delaySamples = (int) (timeMs.load()* 0.001 * currentSampleRate);
    auto wetAmount = mix.load();
    auto dryAmount = 1.0f - wetAmount;
    auto feedbackAmount = juce::jmin (feedback.load(), 0.95f);

    for (int i = 0; i <numSamples; ++i)
    {
        auto blip = testSound.getNextSample();

        for (int ch = 0; ch < numChannels; ++ch)
       {
        auto* data = buffer.getWritePointer (ch);
        auto dry = data[i] + blip;
        auto wet = delays[ch].read (delaySamples);

        delays[ch].write (dry + wet * feedbackAmount);
        data[i] = dry * dryAmount + wet * wetAmount;
       }
    }
}

juce::AudioProcessorEditor* SimpleDelayProcessor::createEditor()
{
    return new SimpleDelayEditor (*this);
}

bool SimpleDelayProcessor::hasEditor() const
{
    return true;
}

const juce::String SimpleDelayProcessor::getName() const
{
    return "Simple Delay";
}

bool SimpleDelayProcessor::acceptsMidi() const
{
    return false;
}

bool SimpleDelayProcessor::producesMidi() const
{
    return false;
}

bool SimpleDelayProcessor::isMidiEffect() const
{
    return false;
}

double SimpleDelayProcessor::getTailLengthSeconds() const
{
    return 10.0;
}

int SimpleDelayProcessor::getNumPrograms()
{
    return 1;
}

int SimpleDelayProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleDelayProcessor::setCurrentProgram (int)
{
}

const juce::String SimpleDelayProcessor::getProgramName (int)
{
    return {};
}

void SimpleDelayProcessor::changeProgramName (int, const juce::String&)
{
}

void SimpleDelayProcessor::getStateInformation (juce::MemoryBlock&)
{
}

void SimpleDelayProcessor::setStateInformation (const void*, int)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleDelayProcessor();
}