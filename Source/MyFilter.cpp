#pragma once
#include <math.h>
#include <JuceHeader.h>
#include "MyFilter.h"


// --------------------------------------------------------------------------------
// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
// --------------------------------------------------------------------------------
CMyFilter::CMyFilter()
{
	// ƒƒ“ƒo[•Ï”‚ð‰Šú‰»
	a0 = 1.0f; // 0ˆÈŠO‚É‚µ‚Ä‚¨‚©‚È‚¢‚ÆœŽZ‚ÅƒGƒ‰[‚É‚È‚é
	a1 = 0.0f;
	a2 = 0.0f;
	b0 = 1.0f;
	b1 = 0.0f;
	b2 = 0.0f;

	in1 = 0.0f;
	in2 = 0.0f;

	out1 = 0.0f;
	out2 = 0.0f;

	samplerate = 44100;
}

// --------------------------------------------------------------------------------
// “ü—ÍM†‚ÉƒtƒBƒ‹ƒ^‚ð“K—p‚·‚éŠÖ”
// --------------------------------------------------------------------------------
float CMyFilter::Process(float in)
{
	if (a0 == 0.0f) {
		return in; // a0 ‚ª 0 ‚Ìê‡A“ü—ÍM†‚ð‚»‚Ì‚Ü‚Ü•Ô‚·
	}

	// “ü—ÍM†‚ÉƒtƒBƒ‹ƒ^‚ð“K—p‚µAo—ÍM†•Ï”‚É•Û‘¶B
	float out = b0 / a0 * in + b1 / a0 * in1 + b2 / a0 * in2
		- a1 / a0 * out1 - a2 / a0 * out2;

	in2 = in1; // 2‚Â‘O‚Ì“ü—ÍM†‚ðXV
	in1 = in;  // 1‚Â‘O‚Ì“ü—ÍM†‚ðXV

	out2 = out1; // 2‚Â‘O‚Ìo—ÍM†‚ðXV
	out1 = out;  // 1‚Â‘O‚Ìo—ÍM†‚ðXV

	// o—ÍM†‚ð•Ô‚·
	return out;
}

// --------------------------------------------------------------------------------
// ƒtƒBƒ‹ƒ^ŒW”‚ðŒvŽZ‚·‚éƒƒ“ƒo[ŠÖ”
// --------------------------------------------------------------------------------
void CMyFilter::LowPass(float freq, float q)
{
	// ƒtƒBƒ‹ƒ^ŒW”ŒvŽZ‚ÅŽg—p‚·‚é’†ŠÔ’l‚ð‹‚ß‚éB
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	// ƒtƒBƒ‹ƒ^ŒW”‚ð‹‚ß‚éB
	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = (1.0f - cos(omega)) / 2.0f;
	b1 = 1.0f - cos(omega);
	b2 = (1.0f - cos(omega)) / 2.0f;
}

void CMyFilter::HighPass(float freq, float q)
{
	// ƒtƒBƒ‹ƒ^ŒW”ŒvŽZ‚ÅŽg—p‚·‚é’†ŠÔ’l‚ð‹‚ß‚éB
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	// ƒtƒBƒ‹ƒ^ŒW”‚ð‹‚ß‚éB
	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = (1.0f + cos(omega)) / 2.0f;
	b1 = -(1.0f + cos(omega));
	b2 = (1.0f + cos(omega)) / 2.0f;
}

void CMyFilter::BandPass(float freq, float bw)
{
	// ƒtƒBƒ‹ƒ^ŒW”ŒvŽZ‚ÅŽg—p‚·‚é’†ŠÔ’l‚ð‹‚ß‚éB
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));

	// ƒtƒBƒ‹ƒ^ŒW”‚ð‹‚ß‚éB
	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = alpha;
	b1 = 0.0f;
	b2 = -alpha;
}

void CMyFilter::Notch(float freq, float bw)
{
	// ƒtƒBƒ‹ƒ^ŒW”ŒvŽZ‚ÅŽg—p‚·‚é’†ŠÔ’l‚ð‹‚ß‚éB
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));

	// ƒtƒBƒ‹ƒ^ŒW”‚ð‹‚ß‚éB
	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = 1.0f;
	b1 = -2.0f * cos(omega);
	b2 = 1.0f;
}

void CMyFilter::LowShelf(float freq, float q, float gain)
{
	// ƒtƒBƒ‹ƒ^ŒW”ŒvŽZ‚ÅŽg—p‚·‚é’†ŠÔ’l‚ð‹‚ß‚éB
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);
	float A = pow(10.0f, (gain / 40.0f));
	float beta = sqrt(A) / q;

	// ƒtƒBƒ‹ƒ^ŒW”‚ð‹‚ß‚éB
	a0 = (A + 1.0f) + (A - 1.0f) * cos(omega) + beta * sin(omega);
	a1 = -2.0f * ((A - 1.0f) + (A + 1.0f) * cos(omega));
	a2 = (A + 1.0f) + (A - 1.0f) * cos(omega) - beta * sin(omega);
	b0 = A * ((A + 1.0f) - (A - 1.0f) * cos(omega) + beta * sin(omega));
	b1 = 2.0f * A * ((A - 1.0f) - (A + 1.0f) * cos(omega));
	b2 = A * ((A + 1.0f) - (A - 1.0f) * cos(omega) - beta * sin(omega));
}

void CMyFilter::HighShelf(float freq, float q, float gain)
{
	// ƒtƒBƒ‹ƒ^ŒW”ŒvŽZ‚ÅŽg—p‚·‚é’†ŠÔ’l‚ð‹‚ß‚éB
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);
	float A = pow(10.0f, (gain / 40.0f));
	float beta = sqrt(A) / q;

	// ƒtƒBƒ‹ƒ^ŒW”‚ð‹‚ß‚éB
	a0 = (A + 1.0f) - (A - 1.0f) * cos(omega) + beta * sin(omega);
	a1 = 2.0f * ((A - 1.0f) - (A + 1.0f) * cos(omega));
	a2 = (A + 1.0f) - (A - 1.0f) * cos(omega) - beta * sin(omega);
	b0 = A * ((A + 1.0f) + (A - 1.0f) * cos(omega) + beta * sin(omega));
	b1 = -2.0f * A * ((A - 1.0f) + (A + 1.0f) * cos(omega));
	b2 = A * ((A + 1.0f) + (A - 1.0f) * cos(omega) - beta * sin(omega));
}


void CMyFilter::Peaking(float freq, float bw, float gain)
{
	// ƒtƒBƒ‹ƒ^ŒW”ŒvŽZ‚ÅŽg—p‚·‚é’†ŠÔ’l‚ð‹‚ß‚éB
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));
	float A = pow(10.0f, (gain / 40.0f));

	// ƒtƒBƒ‹ƒ^ŒW”‚ð‹‚ß‚éB
	a0 = 1.0f + alpha / A;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha / A;
	b0 = 1.0f + alpha * A;
	b1 = -2.0f * cos(omega);
	b2 = 1.0f - alpha * A;
}

void CMyFilter::AllPass(float freq, float q)
{
	// ƒtƒBƒ‹ƒ^ŒW”ŒvŽZ‚ÅŽg—p‚·‚é’†ŠÔ’l‚ð‹‚ß‚éB
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	// ƒtƒBƒ‹ƒ^ŒW”‚ð‹‚ß‚éB
	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = 1.0f - alpha;
	b1 = -2.0f * cos(omega);
	b2 = 1.0f + alpha;
}

void CMyFilter::setSampleRate(float rate) {
	samplerate = rate;
}