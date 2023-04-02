#pragma once
#include <JuceHeader.h>
using namespace juce;

class ParameterManager {
public:
	ParameterManager() {}
	void set(String id, RangedAudioParameter* param) {
		parameters.set(id, param);
	}
	float getValueByID(String id) {
		return parameters[id]->convertFrom0to1(parameters[id]->getValue());
	}
	juce::HashMap<String, RangedAudioParameter*> parameters;
};