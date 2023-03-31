/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Constants.h"
#include "CustomLookAndFeel.h"

//==============================================================================
/**
*/
class MultibandReverbAudioProcessorEditor : public juce::AudioProcessorEditor,
	public juce::ComboBox::Listener//,
	//public juce::Slider::Listener
{
public:
	MultibandReverbAudioProcessorEditor(MultibandReverbAudioProcessor& p,
		juce::AudioProcessorValueTreeState& vts);
	~MultibandReverbAudioProcessorEditor() override;

	//==============================================================================
	void paint(juce::Graphics&) override;
	void resized() override;

	void comboBoxChanged(juce::ComboBox* comboBox) override;
	//void sliderValueChanged(juce::Slider* slider) override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	MultibandReverbAudioProcessor& audioProcessor;

	typedef juce::AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment; // �ǉ�
	typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

	juce::AudioProcessorValueTreeState& valueTreeState;
	std::unique_ptr<ComboBoxAttachment> filterTypeBoxAttachment;
	//std::unique_ptr<SliderAttachment> freqAttachment;

	juce::ComboBox myComboBox;

	juce::Slider freqKnob;
	juce::Slider qKnob;
	juce::Slider bandWidthKnob;
	juce::Slider gainKnob;
	juce::Array <juce::Slider*> sliders;

	juce::Label freqLabel;
	juce::Label qLabel;
	juce::Label bandWidthLabel;
	juce::Label gainLabel;
	juce::Array<juce::Label*> labels;
	//CustomLookAndFeel customLookAndFeel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MultibandReverbAudioProcessorEditor)
};