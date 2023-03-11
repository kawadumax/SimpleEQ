#pragma once;
#include <math.h>


// --------------------------------------------------------------------------------
// CMyFilter
// --------------------------------------------------------------------------------
class CMyFilter
{
private:
	// �t�B���^�̌W��
	float a0, a1, a2, b0, b1, b2;
	// �o�b�t�@
	float out1, out2;
	float in1, in2;

public:
	//inline CMyFilter();

	//// ���͐M���Ƀt�B���^��K�p����֐�
	//inline float Process(float in);

	//// �t�B���^�W�����v�Z���郁���o�[�֐�
	//inline void LowPass(float freq, float q, float samplerate = 44100.0f);
	//inline void HighPass(float freq, float q, float samplerate = 44100.0f);
	//inline void BandPass(float freq, float bw, float samplerate = 44100.0f);
	//inline void Notch(float freq, float bw, float samplerate = 44100.0f);
	//inline void LowShelf(float freq, float q, float gain, float samplerate = 44100.0f);
	//inline void HighShelf(float freq, float q, float gain, float samplerate = 44100.0f);
	//inline void Peaking(float freq, float bw, float gain, float samplerate = 44100.0f);
	//inline void AllPass(float freq, float q, float samplerate = 44100.0f);

	CMyFilter();

	// ���͐M���Ƀt�B���^��K�p����֐�
	float Process(float in);

	// �t�B���^�W�����v�Z���郁���o�[�֐�
	void LowPass(float freq, float q, float samplerate = 44100.0f);
	void HighPass(float freq, float q, float samplerate = 44100.0f);
	void BandPass(float freq, float bw, float samplerate = 44100.0f);
	void Notch(float freq, float bw, float samplerate = 44100.0f);
	void LowShelf(float freq, float q, float gain, float samplerate = 44100.0f);
	void HighShelf(float freq, float q, float gain, float samplerate = 44100.0f);
	void Peaking(float freq, float bw, float gain, float samplerate = 44100.0f);
	void AllPass(float freq, float q, float samplerate = 44100.0f);
};