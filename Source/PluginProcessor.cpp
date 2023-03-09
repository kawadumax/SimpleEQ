/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultibandReverbAudioProcessor::MultibandReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    this->cMyFilter = new CMyFilter();
    this->cMyFilter->LowPass(400.0, 1.0, getSampleRate());
    addParameter(filterType = new juce::AudioParameterChoice("filterTypeID",
        "Filter Type",
        juce::StringArray{ "LowPass","HighPass", "BandPass", 
            "Notch", "LowShelf" , "HighShelf", "Peaking" ,"AllPass"
        },
        0
    ));

}

MultibandReverbAudioProcessor::~MultibandReverbAudioProcessor()
{
    // デストラクタ
    delete this->cMyFilter;
    delete this->filterType;
    
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

void MultibandReverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MultibandReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void MultibandReverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MultibandReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

}

void MultibandReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MultibandReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
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

void MultibandReverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    int choice = this->filterType->getIndex();

    switch (choice) {
    case 0:
        std::cout << "You chose option 0\n";
        this->cMyFilter->LowPass(400.0, 1.0, getSampleRate());
        break;
    case 1:
        std::cout << "You chose option 1\n";
        this->cMyFilter->HighPass(10000.0, 1.0, getSampleRate());
        break;
    case 2:
        std::cout << "You chose option 2\n";
        this->cMyFilter->BandPass(400.0, 1.0, getSampleRate());
        break;
    case 3:
        std::cout << "You chose option 3\n";
        this->cMyFilter->Notch(400.0, 1.0, getSampleRate());
        break;
    case 4:
        std::cout << "You chose option 4\n";
        this->cMyFilter->LowShelf(400.0, 1.0, getSampleRate());
        break;
    case 5:
        std::cout << "You chose option 5\n";
        this->cMyFilter->HighShelf(400.0, 1.0, getSampleRate());
        break;
    case 6:
        std::cout << "You chose option 6\n";
        this->cMyFilter->Peaking(400.0, 1.0, getSampleRate());
        break;
    case 7:
        std::cout << "You chose option 7\n";
        this->cMyFilter->AllPass(400.0, 1.0, getSampleRate());
        break;
    default:
        std::cout << "Invalid choice\n";
    }

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
        int numSamples = buffer.getNumSamples();
        for (auto sample = 0; sample < numSamples; ++sample)
        {
            channelData[sample] = this->cMyFilter->Process(channelData[sample]);
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
    return new MultibandReverbAudioProcessorEditor (*this);
}

//==============================================================================
void MultibandReverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MultibandReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MultibandReverbAudioProcessor();
}
