#pragma once

#include <JuceHeader.h>

class Constants
{
public:
	static juce::NamedValueSet& getConstants()
	{
		static juce::NamedValueSet constants;
		if (constants.isEmpty())
		{
			constants.set("PI", 3.14159);
			constants.set("GRAVITY", 9.81);
			// 他の定数もここでセットする
		}
		return constants;
	}

	inline static const juce::StringArray FILTER_OPTIONS = { "LowPass","HighPass", "BandPass",
				"Notch", "LowShelf" , "HighShelf", "Peaking" ,"AllPass"
	};

	//inline static const juce::var PARAMETER_IDS = {
	//	{"FREQ"}
	//}
	inline static const struct PARAMETER_ID {
		using String = juce::String;
		inline static const String FREQUENCY_ID = "FREQUENCY_ID";
		inline static const String Q_ID = "Q_ID";
		inline static const String BANDWIDTH_ID = "BANDWIDTH_ID";
		inline static const String GAIN_ID = "GAIN_ID";
		inline static const String FILTER_TYPE_ID = "FILTER_TYPE_ID";
	};
};

// Constantsを使う例
//double pi = Constants::getConstants()["PI"];
//double g = Constants::getConstants()["GRAVITY"];