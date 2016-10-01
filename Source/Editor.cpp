/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "Processor.h"
#include "Editor.h"


//==============================================================================
SineConvolutionAudioProcessorEditor::SineConvolutionAudioProcessorEditor (SineConvolutionAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	// these define the parameters of our slider object
	frequency.setSliderStyle(Slider::LinearBarVertical);
	frequency.setRange(50.0, 20000.0, 1.0);
	frequency.setSkewFactorFromMidPoint(500.0); //
	frequency.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	frequency.setPopupDisplayEnabled(true, this);
	frequency.setTextValueSuffix(" Frequency");
	frequency.setValue(1.0);

	frequency.addListener(this);

	// these define the parameters of our slider object
	amplitude.setSliderStyle(Slider::LinearBarVertical);
	amplitude.setRange(0.0, 0.5, 0.005);
	amplitude.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	amplitude.setPopupDisplayEnabled(true, this);
	amplitude.setTextValueSuffix(" Amplitude");
	amplitude.setValue(0.125);

	amplitude.addListener(this);

	// this function adds the slider to the editor
	addAndMakeVisible(&frequency);
	addAndMakeVisible(&amplitude);
}

SineConvolutionAudioProcessorEditor::~SineConvolutionAudioProcessorEditor()
{
}

//==============================================================================
void SineConvolutionAudioProcessorEditor::paint (Graphics& g)
{
	// fill the whole window white
	g.fillAll(Colours::white);

	// set the current drawing colour to black
	g.setColour(Colours::black);

	// set the font size and draw text to the screen
	g.setFont(15.0f);

	g.drawFittedText("Settings", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void SineConvolutionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	frequency.setBounds(40, 30, 20, getHeight() - 60);
	amplitude.setBounds(70, 30, 20, getHeight() - 60);

}

void SineConvolutionAudioProcessorEditor::sliderValueChanged(Slider *slider) {
	processor.mFrequency = (float)frequency.getValue();
	processor.mLevel = (float)amplitude.getValue();
}
