#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

//CustomLookAndFeel::CustomLookAndFeel() {
//
//
//};

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
	// ノブの描画方法をここに記述します。
	// 円周上のスライダーの位置を計算

	float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
	float radius = juce::jmin(width / 2, height / 2) - 10.0f;
	float centerX = x + width * 0.5f;
	float centerY = y + height * 0.5f;
	float thumbRadius = radius * 0.5f;
	float thumbCenterX = centerX + radius * std::cos(angle);
	float thumbCenterY = centerY + radius * std::sin(angle);

	DBG("angle: " + juce::String(angle));

	// スライダーの背景を描画
	g.setColour(juce::Colours::darkgrey);
	//g.drawEllipse(x, y, width, height, 2.0f);
	g.fillEllipse(x, y, width, height);

	// スライダーのつまみを描画
	g.setColour(juce::Colours::white);
	g.fillEllipse(thumbCenterX - thumbRadius * 0.5f, thumbCenterY - thumbRadius * 0.5f, thumbRadius, thumbRadius);
}