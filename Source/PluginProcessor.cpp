/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Constants.h"

using PARAMETER_ID = Constants::PARAMETER_ID;
//==============================================================================
MultibandReverbAudioProcessor::MultibandReverbAudioProcessor() :
#ifndef JucePlugin_PreferredChannelConfigurations
	AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
	), apvts(
		*this, nullptr, "PARAMETERS", {
		std::make_unique<juce::AudioParameterChoice>(
			PARAMETER_ID::FILTER_TYPE_ID,
			"Filter Type",
			Constants::FILTER_OPTIONS,
			0
			),
		std::make_unique<juce::AudioParameterFloat>(
			PARAMETER_ID::FREQUENCY_ID,
			"Frequency",
			juce::NormalisableRange<float>(30.0, 20000.0, 2),
			400
			),
		std::make_unique<juce::AudioParameterFloat>(
			PARAMETER_ID::Q_ID,
			"Q",
			juce::NormalisableRange<float>(0.0, 1.0, 0.01),
			0.5
			),
		std::make_unique<juce::AudioParameterFloat>(
			PARAMETER_ID::BANDWIDTH_ID,
			"Bandwidth",
			juce::NormalisableRange<float>(0.0, 1.0, 0.01),
			0.5
			),
		std::make_unique<juce::AudioParameterFloat>(
			PARAMETER_ID::GAIN_ID,
			"Gain",
			juce::NormalisableRange<float>(0.0, 1.0, 0.01),
			0.5
			),
		}
	), cMyFilter()

#endif
{
	DBG("Procrssor Initializing");

	apvts.addParameterListener(PARAMETER_ID::FREQUENCY_ID, this);
	apvts.addParameterListener(PARAMETER_ID::Q_ID, this);
	apvts.addParameterListener(PARAMETER_ID::BANDWIDTH_ID, this);
	apvts.addParameterListener(PARAMETER_ID::GAIN_ID, this);
	apvts.addParameterListener(PARAMETER_ID::FILTER_TYPE_ID, this);

	parameterManager.set(PARAMETER_ID::FREQUENCY_ID, apvts.getParameter(PARAMETER_ID::FREQUENCY_ID));
	parameterManager.set(PARAMETER_ID::Q_ID, apvts.getParameter(PARAMETER_ID::Q_ID));
	parameterManager.set(PARAMETER_ID::BANDWIDTH_ID, apvts.getParameter(PARAMETER_ID::BANDWIDTH_ID));
	parameterManager.set(PARAMETER_ID::GAIN_ID, apvts.getParameter(PARAMETER_ID::GAIN_ID));
	parameterManager.set(PARAMETER_ID::FILTER_TYPE_ID, apvts.getParameter(PARAMETER_ID::FILTER_TYPE_ID));
}

MultibandReverbAudioProcessor::~MultibandReverbAudioProcessor()
{

}

//==============================================================================
const juce::String MultibandReverbAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool MultibandReverbAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool MultibandReverbAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool MultibandReverbAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double MultibandReverbAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int MultibandReverbAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
	// so this should be at least 1, even if you're not really implementing programs.
}

int MultibandReverbAudioProcessor::getCurrentProgram()
{
	return 0;
}

void MultibandReverbAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String MultibandReverbAudioProcessor::getProgramName(int index)
{
	return {};
}

void MultibandReverbAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void MultibandReverbAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
	cMyFilter.setSampleRate(sampleRate);
	const auto f = parameterManager.getValueByID(PARAMETER_ID::FREQUENCY_ID);
	const auto q = parameterManager.getValueByID(PARAMETER_ID::Q_ID);
	cMyFilter.LowPass(f, q);

}

void MultibandReverbAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MultibandReverbAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	// Some plugin hosts, such as certain GarageBand versions, will only
	// load plugins that support stereo bus layouts.
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void MultibandReverbAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	juce::ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	// This is the place where you'd normally do the guts of your plugin's
	// audio processing...
	// Make sure to reset the state if your inner loop is processing
	// the samples and the outer loop is handling the channels.
	// Alternatively, you can process the samples with the channels
	// interleaved by keeping the same state.
	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);

		// ..do something to the data...
		int numSamples = buffer.getNumSamples();
		for (auto sample = 0; sample < numSamples; ++sample)
		{
			channelData[sample] = cMyFilter.Process(channelData[sample]);
		}
	}
}

//==============================================================================
bool MultibandReverbAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MultibandReverbAudioProcessor::createEditor()
{
	return new MultibandReverbAudioProcessorEditor(*this, apvts);
}

//==============================================================================
void MultibandReverbAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void MultibandReverbAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//void MultibandReverbAudioProcessor::parameterGestureChanged(int parameterIndex, bool gestureIsStarting)
//{
//	// nothing to do
//	DBG("You Gestured");
//}

void MultibandReverbAudioProcessor::changeFilterType(float choice)
{
	// This method will be called whenever the parameter's value changes
	//const auto f = apvts.getParameter(PARAMETER_ID::FREQUENCY_ID)->getValue();
	//const auto q = apvts.getParameter(PARAMETER_ID::Q_ID)->getValue();
	//const auto bw = apvts.getParameter(PARAMETER_ID::BANDWIDTH_ID)->getValue();
	//const auto g = apvts.getParameter(PARAMETER_ID::GAIN_ID)->getValue();

	const auto f = parameterManager.getValueByID(PARAMETER_ID::FREQUENCY_ID);
	const auto q = parameterManager.getValueByID(PARAMETER_ID::Q_ID);
	const auto bw = parameterManager.getValueByID(PARAMETER_ID::BANDWIDTH_ID);
	const auto g = parameterManager.getValueByID(PARAMETER_ID::GAIN_ID);

	switch (int(choice)) {
	case 0:
		DBG("You chose option 0");
		cMyFilter.LowPass(f, q);
		break;
	case 1:
		DBG("You chose option 1");
		cMyFilter.HighPass(f, q);
		break;
	case 2:
		DBG("You chose option 2");
		cMyFilter.BandPass(f, bw);
		break;
	case 3:
		DBG("You chose option 3");
		cMyFilter.Notch(f, bw);
		break;
	case 4:
		DBG("You chose option 4");
		cMyFilter.LowShelf(f, q, g);
		break;
	case 5:
		DBG("You chose option 5");
		cMyFilter.HighShelf(f, q, g);
		break;
	case 6:
		DBG("You chose option 6");
		cMyFilter.Peaking(f, bw, g);
		break;
	case 7:
		DBG("You chose option 7");
		cMyFilter.AllPass(f, q);
		break;
	default:
		DBG("Invalid choice");
	}
}

void MultibandReverbAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
	DBG("Parameter value changed : ID = " +
		parameterID + " value = " + juce::String(newValue)
	);

	if (parameterID == Constants::PARAMETER_ID::FILTER_TYPE_ID) {
		changeFilterType(newValue);
	}
	else {
		const auto filterType = apvts.getParameter(PARAMETER_ID::FILTER_TYPE_ID)->getValue();
		changeFilterType(filterType);
	}
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new MultibandReverbAudioProcessor();
}
