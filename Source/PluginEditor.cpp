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
SimpleEQAudioProcessorEditor::SimpleEQAudioProcessorEditor(SimpleEQAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
	: AudioProcessorEditor(&p), audioProcessor(p), valueTreeState(vts)
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
	filterTypeBoxAttachment.reset(new ComboBoxAttachment(valueTreeState, Constants::PARAMETER_ID::FILTER_TYPE_ID, filterTypeComboBox)); // ’Ç‰Á

	//// Add the ComboBox to this component
	addAndMakeVisible(filterTypeComboBox);

	//Setting for Knobs

	for (int index = 0; index < Constants::CONTROLS.size(); ++index)
	{

		auto slider = std::make_unique<juce::Slider>();
		slider->setRange(0.0, 1.0, 0.01);
		slider->setSliderStyle(juce::Slider::SliderStyle::Rotary);
		slider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, knobRange * 0.5, fontSize + 5);
		slider->setBounds(
			startKnobPosX + (knobRange + knobPadding) * index - knobRange * 0.5,
			height * 0.75 - knobRange * 0.5,
			knobRange,
			knobRange
		);
		//slider->setLookAndFeel(&customLookAndFeel);
		slider->setRotaryParameters(startAngle, endAngle, true);

		//Make label for knobs
		auto label = std::make_unique<juce::Label>();
		label->setFont(juce::Font(fontSize));
		label->setText(Constants::CONTROLS[index].name, juce::dontSendNotification);
		label->setJustificationType(juce::Justification::centred);
		label->setBounds(
			slider->getX(),
			slider->getBottom() - 5,
			slider->getWidth(),
			fontSize
		);

		addAndMakeVisible(slider.get());
		addAndMakeVisible(label.get());

		auto attachment = std::make_unique<SliderAttachment>(valueTreeState, Constants::CONTROLS[index].id, *slider);
		attachment.reset(new SliderAttachment(valueTreeState, Constants::CONTROLS[index].id, *slider));

		// Add the slider, label, and attachment to a new Controll instance
		controls.add(Controll(std::move(slider), std::move(label), std::move(attachment)));

	}
}

SimpleEQAudioProcessorEditor::~SimpleEQAudioProcessorEditor()
{
	DBG("Editor Destructed");
	for (auto& control : controls)
	{
		control.attachment.reset();
	}
}

//==============================================================================
void SimpleEQAudioProcessorEditor::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colour(50, 62, 68));

}

void SimpleEQAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	// 

}