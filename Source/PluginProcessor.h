/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MyFilter.h"
#include "Constants.h"
#include "ParameterManager.h"
//==============================================================================

class SimpleEQAudioProcessor : public juce::AudioProcessor
#if JucePlugin_Enable_ARA
	, public juce::AudioProcessorARAExtension
#endif
	, public juce::AudioProcessorValueTreeState::Listener
{
public:
	//==============================================================================
	SimpleEQAudioProcessor();
	~SimpleEQAudioProcessor() override;

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

	//==============================================================================
	juce::AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const juce::String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const juce::String getProgramName(int index) override;
	void changeProgramName(int index, const juce::String& newName) override;

	//==============================================================================
	void getStateInformation(juce::MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;

	//void parameterValueChanged(int parameterIndex, float newValue) override;
	//void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override;
	void parameterChanged(const juce::String& parameterID, float newValue) override;

private:

	void changeFilterType(float choice);

	juce::AudioProcessorValueTreeState apvts;
	//juce::HashMap<String, AudioParameterFloat*> parameters;
	ParameterManager parameterManager;
	CMyFilter cMyFilter;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleEQAudioProcessor)
};
