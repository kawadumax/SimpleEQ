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
	public juce::Button::Listener,
	public juce::ComboBox::Listener,
	public juce::Slider::Listener
{
public:
	MultibandReverbAudioProcessorEditor(MultibandReverbAudioProcessor&,
		juce::AudioProcessorValueTreeState& vts);
	~MultibandReverbAudioProcessorEditor() override;

	//==============================================================================
	void paint(juce::Graphics&) override;
	void resized() override;

	void buttonClicked(juce::Button* button) override;
	void comboBoxChanged(juce::ComboBox* comboBox) override;
	void sliderValueChanged(juce::Slider* slider) override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	MultibandReverbAudioProcessor& audioProcessor;

	typedef juce::AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment; // �ǉ�

	juce::AudioProcessorValueTreeState& valueTreeState; // �ǉ�
	std::unique_ptr<ComboBoxAttachment> filterTypeBoxAttachment;

	juce::TextButton myButton;
	juce::ComboBox myComboBox;
	juce::Slider lowPassKnob;
	CustomLookAndFeel customLookAndFeel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MultibandReverbAudioProcessorEditor)
};