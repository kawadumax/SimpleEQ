/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//#include <MyFilter.h>
#include "MyFilter.h"

//==============================================================================
/**
*/
class MultibandReverbAudioProcessor : public juce::AudioProcessor
#if JucePlugin_Enable_ARA
	, public juce::AudioProcessorARAExtension
#endif
	, public juce::AudioParameterChoice::Listener
{
public:
	//==============================================================================
	MultibandReverbAudioProcessor();
	~MultibandReverbAudioProcessor() override;

	/// <summary>
	/// フィルタ用のクラス
	/// </summary>
	CMyFilter* cMyFilter;
	//juce::AudioParameterChoiceAttributes attributes = juce::AudioParameterChoiceAttributes().withLabel("selected");
	//param = std::make_unique<juce::AudioParameterChoice> ("paramID", "Parameter Name", juce::StringArray{ "a", "b", "c" }, 0, attributes);

	/// <summary>
	/// プラグイン全体の状態を保持するインスタンス
	/// </summary>
	//juce::AudioProcessorValueTreeState treeState;

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

	void parameterValueChanged(int parameterIndex, float newValue) override;
	void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override;

private:
	juce::AudioParameterChoice* filterType;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MultibandReverbAudioProcessor)
};
