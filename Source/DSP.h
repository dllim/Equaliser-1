/*
  ==============================================================================

    DSP.h
    Created: 27 Nov 2018 11:53:35pm
    Author:  daryl

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class DSP
{
public:
	DSP() {}
	~DSP() {}

	struct coefficients {
		float b0; float b1; float b2;
		float a0; float a1; float a2;
	};

	dsp::IIR::Coefficients<float>::Ptr newCoefficients;
	dsp::IIR::Coefficients<float>::Ptr test2;

	static const dsp::IIR::Coefficients<float>::Ptr calculusCoefficients(float frequency, float Q, float gain,
		int type, double sampleRate,
		float &b0, float &b1, float &b2, float &a1, float &a2);

	static const double getMagnitudeForFrequency(double frequency, double sampleRate,
		const float b0, const float b1, const float b2, const float a1, const float a2);

	static const double getPhaseForFrequency(double frequency, double sampleRate,
		const float b0, const float b1, const float b2, const float a1, const float a2);
};
