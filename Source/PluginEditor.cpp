/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#include <iterator>
#include <vector>
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MultibandReverbAudioProcessorEditor::MultibandReverbAudioProcessorEditor(MultibandReverbAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
	: AudioProcessorEditor(&p), audioProcessor(p), valueTreeState(vts),
	freqKnob(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::NoTextBox),
	qKnob(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::NoTextBox),
	bandWidthKnob(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::NoTextBox),
	gainKnob(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::NoTextBox),
	sliders({ &freqKnob, &qKnob, &bandWidthKnob, &gainKnob })
{
	const int width = 600;
	const int height = 300;
	const int knobRange = 75;
	const int knobPadding = 25;
	const int centerX = width / 2;
	const int centerY = height / 2;
	const int startKnobPosX = centerX - (knobRange * 2 + knobPadding * 1.5) + knobRange * 0.5;
	const float startAngle = juce::MathConstants<float>::pi * 210.0f / 180.0f;
	const float endAngle = juce::MathConstants<float>::pi * 510.0f / 180.0f;

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(width, height);

	// Create a TextButton
	myButton.setButtonText("Click me!");
	myButton.addListener(this);
	addAndMakeVisible(myButton);

	// Create a ComboBox
	myComboBox.addItemList(Constants::FILTER_OPTIONS, 1);

	// Attach this component as a listener for the ComboBox
	myComboBox.addListener(this);

	filterTypeBoxAttachment.reset(new ComboBoxAttachment(valueTreeState, "FilterTypeID", myComboBox)); // ’Ç‰Á

	// Add the ComboBox to this component
	addAndMakeVisible(myComboBox);

	//Setting for Knobs

	for (int index = 0; index < sliders.size(); ++index)
	{
		const auto& slider = sliders[index];
		slider->setRange(0.0, 1.0, 0.01);
		slider->setValue(0.5);
		slider->setBounds(
			startKnobPosX + (knobRange + knobPadding) * index - knobRange * 0.5,
			height * 0.75 - knobRange * 0.5,
			knobRange,
			knobRange
		);
		//slider->setLookAndFeel(&customLookAndFeel);
		slider->setRotaryParameters(startAngle, endAngle, true);
		slider->addListener(this);
		addAndMakeVisible(slider);

	}
}

MultibandReverbAudioProcessorEditor::~MultibandReverbAudioProcessorEditor()
{
}

//==============================================================================
void MultibandReverbAudioProcessorEditor::paint(juce::Graphics& g)
{


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

void MultibandReverbAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
	//if (slider == &lowPassKnob) {
		// Handle button click here
	DBG("LowPassKnob Changed!");
	//}
	slider->repaint();
}