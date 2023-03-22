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

	//static const int FOO = 42;
	//static const double BAR = 3.14;
	inline static const juce::StringArray FILTER_OPTIONS = { "LowPass","HighPass", "BandPass",
				"Notch", "LowShelf" , "HighShelf", "Peaking" ,"AllPass"
	};
};

// Constantsを使う例
//double pi = Constants::getConstants()["PI"];
//double g = Constants::getConstants()["GRAVITY"];