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
	freqKnob(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxAbove),
	qKnob(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxAbove),
	bandWidthKnob(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxAbove),
	gainKnob(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxAbove),
	sliders({ &freqKnob, &qKnob, &bandWidthKnob, &gainKnob }),
	freqLabel("FrequencyLabel", "Frequency"),
	qLabel("QLabel", "Q"),
	bandWidthLabel("BandWidthLabel", "Bandwidth"),
	gainLabel("GainLabel", "Gain"),
	labels({ &freqLabel, &qLabel, &bandWidthLabel, &gainLabel })
{
	DBG("Editor Constructed");
	constexpr int width = 600;
	constexpr int height = 300;
	constexpr int knobRange = 100;
	constexpr int knobPadding = 25;
	constexpr float centerX = width / 2;
	constexpr float centerY = height / 2;
	constexpr float startKnobPosX = centerX - (knobRange * 2 + knobPadding * 1.5) + knobRange * 0.5;
	constexpr float startAngle = juce::MathConstants<float>::pi * 210.0f / 180.0f;
	constexpr float endAngle = juce::MathConstants<float>::pi * 510.0f / 180.0f;
	constexpr float fontSize = 14.0f;

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(width, height);

	// Create a ComboBox
	filterTypeComboBox.addItemList(Constants::FILTER_OPTIONS, 1);
	filterTypeComboBox.setBounds(10, 50, 100, 30);

	//// Attach this component as a listener for the ComboBox
	//filterTypeComboBox.addListener(this);

	filterTypeBoxAttachment.reset(new ComboBoxAttachment(valueTreeState, Constants::PARAMETER_ID::FILTER_TYPE_ID, filterTypeComboBox)); // ’Ç‰Á

	//// Add the ComboBox to this component
	addAndMakeVisible(filterTypeComboBox);

	//Setting for Knobs
	freqAttachment.reset(new SliderAttachment(valueTreeState, Constants::PARAMETER_ID::FREQUENCY_ID, freqKnob));
	qAttachment.reset(new SliderAttachment(valueTreeState, Constants::PARAMETER_ID::Q_ID, qKnob));
	bandwidthAttachment.reset(new SliderAttachment(valueTreeState, Constants::PARAMETER_ID::BANDWIDTH_ID, bandWidthKnob));
	gainAttachment.reset(new SliderAttachment(valueTreeState, Constants::PARAMETER_ID::GAIN_ID, gainKnob));

	for (int index = 0; index < sliders.size(); ++index)
	{
		const auto& slider = sliders[index];
		slider->setRange(0.0, 1.0, 0.01);
		slider->setBounds(
			startKnobPosX + (knobRange + knobPadding) * index - knobRange * 0.5,
			height * 0.75 - knobRange * 0.5,
			knobRange,
			knobRange
		);
		//slider->setLookAndFeel(&customLookAndFeel);
		slider->setRotaryParameters(startAngle, endAngle, true);
		//slider->addListener(this);
		addAndMakeVisible(slider);

		//Make label for knobs
		const auto& label = labels[index];
		label->setFont(juce::Font(fontSize));
		label->setJustificationType(juce::Justification::centred);
		label->setBounds(
			slider->getX(),
			slider->getBottom(),
			slider->getWidth(),
			fontSize
		);
		addAndMakeVisible(label);
	}
}

MultibandReverbAudioProcessorEditor::~MultibandReverbAudioProcessorEditor()
{
	DBG("Editor Destructed");
	freqAttachment.reset();
	qAttachment.reset();
	bandwidthAttachment.reset();
	gainAttachment.reset();
}

//==============================================================================
void MultibandReverbAudioProcessorEditor::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colour(50, 62, 68));

}

void MultibandReverbAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	// 

}