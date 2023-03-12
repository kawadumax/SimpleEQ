/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultibandReverbAudioProcessorEditor::MultibandReverbAudioProcessorEditor(MultibandReverbAudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(400, 300);

	// Create a TextButton
	myButton.setButtonText("Click me!");
	myButton.addListener(this);

	// Add the TextButton to this component
	addAndMakeVisible(myButton);

	// Create a ComboBox
	myComboBox.addItem("UHO", 1);
	myComboBox.addItem("AHO", 2);
	myComboBox.addItem("OHO", 3);

	// Attach this component as a listener for the ComboBox
	myComboBox.addListener(this);

	// Add the ComboBox to this component
	addAndMakeVisible(myComboBox);
}

MultibandReverbAudioProcessorEditor::~MultibandReverbAudioProcessorEditor()
{
}

//==============================================================================
void MultibandReverbAudioProcessorEditor::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	g.setColour(juce::Colours::white);
	g.setFont(15.0f);
	g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);


}

void MultibandReverbAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	// 
	// Set the bounds of the TextButton
	myButton.setBounds(10, 10, 100, 30);

	// Set the bounds of the ComboBox
	myComboBox.setBounds(10, 50, 100, 30);
}

void MultibandReverbAudioProcessorEditor::buttonClicked(juce::Button* button)
{
	if (button == &myButton) {
		// Handle button click here
		DBG("Button Clicked!");
	}
}

void MultibandReverbAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBox)
{
	if (comboBox == &myComboBox) {
		int selectedId = comboBox->getSelectedId();
		juce::String s = "Selected item ID: " + juce::String(selectedId);
		DBG(s);
	}
}