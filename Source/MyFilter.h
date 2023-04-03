#pragma once
#include <math.h>


// --------------------------------------------------------------------------------
// CMyFilter
// --------------------------------------------------------------------------------
class CMyFilter
{
private:

	float a0, a1, a2, b0, b1, b2;
	float out1, out2;
	float in1, in2;

	float samplerate;

public:

	CMyFilter();

	float Process(float in);

	void setSampleRate(float rate);

	void LowPass(float freq, float q);
	void HighPass(float freq, float q);
	void BandPass(float freq, float bw);
	void Notch(float freq, float bw);
	void LowShelf(float freq, float q, float gain);
	void HighShelf(float freq, float q, float gain);
	void Peaking(float freq, float bw, float gain);
	void AllPass(float freq, float q);
};