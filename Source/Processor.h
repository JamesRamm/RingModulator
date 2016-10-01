/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class SineConvolutionAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SineConvolutionAudioProcessor();
    ~SineConvolutionAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void updateAngleDelta(double freq, double sampleRate);
	float mFrequency = 100.0;
	float mLevel = 0.125f;

private:
    //==============================================================================
	float mAngle, mAngleDelta;
	void basic_convolve(float* in, float* out, int length, float* kernel, int kernel_length);
	void generateSineWave(float *&buffer, float nSamples);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SineConvolutionAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
