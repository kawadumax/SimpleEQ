#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

//CustomLookAndFeel::CustomLookAndFeel() {
//
//
//};

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
	// �m�u�̕`����@�������ɋL�q���܂��B
	// �~����̃X���C�_�[�̈ʒu���v�Z
	float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
	float radius = juce::jmin(width / 2, height / 2) - 4.0f;
	float centerX = x + width * 0.5f;
	float centerY = y + height * 0.5f;
	float thumbX = centerX + radius * std::cos(angle);
	float thumbY = centerY + radius * std::sin(angle);

	// �X���C�_�[�̔w�i��`��
	g.setColour(juce::Colours::darkgrey);
	g.drawEllipse(x, y, width, height, 2.0f);

	// �X���C�_�[�̂܂݂�`��
	g.setColour(juce::Colours::white);
	g.fillEllipse(thumbX - 5, thumbY - 5, 10, 10);
}