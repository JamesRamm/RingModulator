/*
  ==============================================================================

  ==============================================================================
*/

#include "Processor.h"
#include "Editor.h"


//==============================================================================
RingModAudioProcessor::RingModAudioProcessor()
{
}

RingModAudioProcessor::~RingModAudioProcessor()
{
}

//==============================================================================
const String RingModAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RingModAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RingModAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double RingModAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RingModAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RingModAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RingModAudioProcessor::setCurrentProgram (int index)
{
}

const String RingModAudioProcessor::getProgramName (int index)
{
    return String();
}

void RingModAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void RingModAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void RingModAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RingModAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void RingModAudioProcessor::generateSineWave(float *&buffer, float nSamples)
{
	float currentSample;
	for (int sample = 0; sample < nSamples; ++sample)
	{
		currentSample = (float)std::sin(mAngle);
		mAngle += mAngleDelta;
		buffer[sample] = currentSample * mLevel;
	}
}

void RingModAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{

	updateAngleDelta(mFrequency, getSampleRate());
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

	int nSamples = buffer.getNumSamples();  

	// Generate sine wave
	float *sineWave = new (std::nothrow) float[nSamples];
	generateSineWave(sineWave, nSamples);

	// In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, nSamples);

    //Process each channel
	int iSample, channel;
    for (channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);		 

		// multiply with the sine wave
		for (iSample = 0; iSample < nSamples; ++iSample) {
			channelData[iSample] *= sineWave[iSample];
		}
    }

	delete sineWave;
}

void RingModAudioProcessor::updateAngleDelta(double freq, double sampleRate)
{
	const double cyclesPerSample = freq / sampleRate; // [2]
	mAngleDelta = (float)(cyclesPerSample * 2.0 * double_Pi);                                // [3]
}

//==============================================================================
bool RingModAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* RingModAudioProcessor::createEditor()
{
    return new RingModAudioProcessorEditor (*this);
}

//==============================================================================
void RingModAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void RingModAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RingModAudioProcessor();
}
