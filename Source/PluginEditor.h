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
#include "Controll.h"

//==============================================================================
/**
*/
class SimpleEQAudioProcessorEditor : public juce::AudioProcessorEditor

{
public:
	SimpleEQAudioProcessorEditor(SimpleEQAudioProcessor& p,
		juce::AudioProcessorValueTreeState& vts);
	~SimpleEQAudioProcessorEditor() override;

	//==============================================================================
	void paint(juce::Graphics&) override;
	void resized() override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	SimpleEQAudioProcessor& audioProcessor;

	typedef juce::AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment; // ’Ç‰Á
	typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

	juce::AudioProcessorValueTreeState& valueTreeState;
	std::unique_ptr<ComboBoxAttachment> filterTypeBoxAttachment;

	juce::ComboBox filterTypeComboBox;

	//CustomLookAndFeel customLookAndFeel;

	juce::Array<Controll> controls;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleEQAudioProcessorEditor)
};