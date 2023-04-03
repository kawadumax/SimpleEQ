#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
	// ƒmƒu‚Ì•`‰æ•û–@‚ð‚±‚±‚É‹Lq‚µ‚Ü‚·B
	// ‰~Žüã‚ÌƒXƒ‰ƒCƒ_[‚ÌˆÊ’u‚ðŒvŽZ

	float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
	float radius = juce::jmin(width / 2, height / 2) - 10.0f;
	float centerX = x + width * 0.5f;
	float centerY = y + height * 0.5f;
	float thumbRadius = radius * 0.5f;
	float thumbCenterX = centerX + radius * std::cos(angle);
	float thumbCenterY = centerY + radius * std::sin(angle);

	DBG("angle: " + juce::String(angle));

	// ƒXƒ‰ƒCƒ_[‚Ì”wŒi‚ð•`‰æ
	g.setColour(juce::Colours::darkgrey);
	//g.drawEllipse(x, y, width, height, 2.0f);
	g.fillEllipse(x, y, width, height);

	// ƒXƒ‰ƒCƒ_[‚Ì‚Â‚Ü‚Ý‚ð•`‰æ
	g.setColour(juce::Colours::white);
	g.fillEllipse(thumbCenterX - thumbRadius * 0.5f, thumbCenterY - thumbRadius * 0.5f, thumbRadius, thumbRadius);
}