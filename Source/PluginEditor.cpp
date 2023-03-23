/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MultibandReverbAudioProcessorEditor::MultibandReverbAudioProcessorEditor(MultibandReverbAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
	: AudioProcessorEditor(&p), audioProcessor(p), valueTreeState(vts),
	lowPassKnob(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::NoTextBox)
{

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(400, 300);

	// Create a TextButton
	myButton.setButtonText("Click me!");
	myButton.addListener(this);
	addAndMakeVisible(myButton);

	// Create a ComboBox
	myComboBox.addItemList(Constants::FILTER_OPTIONS, 1);

	// Attach this component as a listener for the ComboBox
	myComboBox.addListener(this);

	filterTypeBoxAttachment.reset(new ComboBoxAttachment(valueTreeState, "FilterTypeID", myComboBox)); // 追加

	// Add the ComboBox to this component
	addAndMakeVisible(myComboBox);

	//create LowPassKnob

	// スライダーの範囲を設定する
	lowPassKnob.setRange(0.0, 1.0, 0.01);

	// スライダーの初期値を設定する
	lowPassKnob.setValue(0.5);

	// スライダーの位置とサイズを設定する
	lowPassKnob.setBounds(200 - 25, 150 - 25, 50, 50);
	lowPassKnob.setLookAndFeel(&customLookAndFeel);
	lowPassKnob.addListener(this);
	addAndMakeVisible(lowPassKnob);
}

MultibandReverbAudioProcessorEditor::~MultibandReverbAudioProcessorEditor()
{
}

//==============================================================================
void MultibandReverbAudioProcessorEditor::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	//g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	//g.setColour(juce::Colours::white);
	//g.setFont(15.0f);
	//g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);

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
	if (slider == &lowPassKnob) {
		// Handle button click here
		DBG("LowPassKnob Changed!");
	}
	slider->repaint();
}