#include "DSP.h"

const void DSP::calculusCoefficients(float frequency, float Q, float gain,
	int type, double sampleRate,
	float &b0, float &b1, float &b2, float &a1, float &a2)
{
	auto Ts = (float)(1.0 / sampleRate);
	auto w0 = (float)(2.0 * double_Pi * frequency);
	auto A = (float)(Decibels::decibelsToGain(gain / 2.0));

	auto Ts2 = Ts * Ts;
	auto w02 = w0 * w0;
	auto A2 = A * A;

	auto a0 = Ts * w0 + 2.0f;

	b0 = (Ts * w0) / a0;
	b1 = (Ts * w0) / a0;
	b2 = 0.0f;

	a1 = (Ts * w0 - 2.0f) / a0;
	a2 = 0.0f;
}

const double DSP::getMagnitudeForFrequency(double frequency, double sampleRate,
	const float b0, const float b1, const float b2, const float a1, const float a2)
{
	constexpr std::complex<double> j(0, 1);

	jassert(frequency >= 0 && frequency <= sampleRate * 0.5);

	std::complex<double> numerator = 0.0, denominator = 0.0, factor = 1.0;
	std::complex<double> expjwT = std::exp(-MathConstants<double>::twoPi * frequency * j / sampleRate);

	numerator += ((double)b0) * factor; factor *= expjwT;
	numerator += ((double)b1) * factor; factor *= expjwT;
	numerator += ((double)b2) * factor;

	denominator = 1.0;
	factor = expjwT;

	denominator += ((double)a1) * factor; factor *= expjwT;
	denominator += ((double)a2) * factor;

	return std::abs(numerator / denominator);
}

const double DSP::getPhaseForFrequency(double frequency, double sampleRate,
	const float b0, const float b1, const float b2, const float a1, const float a2)
{
	constexpr std::complex<double> j(0, 1);

	jassert(frequency >= 0 && frequency <= sampleRate * 0.5);

	std::complex<double> numerator = 0.0, denominator = 0.0, factor = 1.0;
	std::complex<double> expjwT = std::exp(-MathConstants<double>::twoPi * frequency * j / sampleRate);

	numerator += ((double)b0) * factor; factor *= expjwT;
	numerator += ((double)b1) * factor; factor *= expjwT;
	numerator += ((double)b2) * factor;

	denominator = 1.0;
	factor = expjwT;

	denominator += ((double)a1) * factor; factor *= expjwT;
	denominator += ((double)a2) * factor;

	return std::arg(numerator / denominator);
}