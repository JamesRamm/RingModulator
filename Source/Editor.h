/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Processor.h"


//==============================================================================
/**
*/
class RingModAudioProcessorEditor  : public AudioProcessorEditor,
											 private Slider::Listener
{
public:
    RingModAudioProcessorEditor (RingModAudioProcessor&);
    ~RingModAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
	void sliderValueChanged(Slider* slider) override;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    RingModAudioProcessor& processor;

	Slider frequency;
	Slider amplitude;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RingModAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
