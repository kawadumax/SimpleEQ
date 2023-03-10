/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultibandReverbAudioProcessorEditor::MultibandReverbAudioProcessorEditor (MultibandReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    // Create a TextButton
    myButton.setButtonText("Click me!");
    myButton.addListener(this);

    // Add the TextButton to this component
    addAndMakeVisible(myButton);
}

MultibandReverbAudioProcessorEditor::~MultibandReverbAudioProcessorEditor()
{
}

//==============================================================================
void MultibandReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);


}

void MultibandReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // 
    // Set the bounds of the TextButton
    myButton.setBounds(10, 10, 100, 30);
}

void MultibandReverbAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &myButton) {
        // Handle button click here
        std::cout << "Button clicked!\n";
    }
}