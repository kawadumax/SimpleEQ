/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MultibandReverbAudioProcessorEditor  : public juce::AudioProcessorEditor,
    public juce::Button::Listener
{
public:
    MultibandReverbAudioProcessorEditor (MultibandReverbAudioProcessor&);
    ~MultibandReverbAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MultibandReverbAudioProcessor& audioProcessor;
    juce::TextButton myButton;
    juce::ComboBox myComboBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultibandReverbAudioProcessorEditor)
};
