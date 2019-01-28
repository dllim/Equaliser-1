/*
Copyright(c) 2018, Daniel Walz - Foleys Finest Audio UG All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met :

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

template<typename Type> 
class Analyser : public Thread
{
public:
	Analyser() : Thread("Filter-Analyser"),
		         abstractFifo (48000), 
			     fft (12),
			     windowing(size_t(fft.getSize()), dsp::WindowingFunction<Type>::kaiser, true, 4) {}
	
	~Analyser() {}

	void addAudioData(const AudioBuffer<Type>&buffer, int startChannel, int numChannels)
	{
		if (abstractFifo.getFreeSpace() < buffer.getNumSamples())
			return;

		int start1, block1, start2, block2;
		abstractFifo.prepareToWrite(buffer.getNumSamples(), start1, block1, start2, block2);
		audioFifo.copyFrom(0, start1, buffer.getReadPointer(startChannel), block1);
		if (block2 > 0)
			audioFifo.copyFrom(0, start2, buffer.getReadPointer(startChannel, block1), block2);

		for (int channel = startChannel + 1; channel < startChannel + numChannels; ++channel)
		{
			if (block1 > 0) audioFifo.addFrom(0, start1, buffer.getReadPointer(channel), block1);
			if (block2 > 0) audioFifo.addFrom(0, start2, buffer.getReadPointer(channel, block1), block2);
		}
		abstractFifo.finishedWrite(block1 + block2);
		waitForData.signal();
	}

	void setupAnalyser(int audioFifoSize, Type sampleRateToUse)
	{
		sampleRate = sampleRateToUse;
		audioFifo.setSize(1, audioFifoSize);
		abstractFifo.setTotalSize(audioFifoSize);
		fftBuffer.setSize(1, fft.getSize() * 2);
		averager.setSize(5, fft.getSize() / 2, false, true);

		startThread(5);
	}

	void run() override
	{
		while (!threadShouldExit())
		{
			if (abstractFifo.getNumReady() >= fft.getSize())
			{
				fftBuffer.clear();

				int start1, block1, start2, block2;
				abstractFifo.prepareToRead(fft.getSize(), start1, block1, start2, block2);
				if (block1 > 0) fftBuffer.copyFrom(0, 0, audioFifo.getReadPointer(0, start1), block1);
				if (block2 > 0) fftBuffer.copyFrom(0, block1, audioFifo.getReadPointer(0, start2), block2);
				abstractFifo.finishedRead((block1 + block2) / 2);

				windowing.multiplyWithWindowingTable(fftBuffer.getWritePointer(0), size_t(fft.getSize()));
				fft.performFrequencyOnlyForwardTransform(fftBuffer.getWritePointer(0));

				ScopedLock lockedForWriting(pathCreationLock);
				averager.addFrom(0, 0, averager.getReadPointer(averagerPtr), averager.getNumSamples(), -1.0f);
				averager.copyFrom(averagerPtr, 0, fftBuffer.getReadPointer(0), averager.getNumSamples(), 1.0f / (averager.getNumSamples() * (averager.getNumChannels() - 1)));
				averager.addFrom(0, 0, averager.getReadPointer(averagerPtr), averager.getNumSamples());
				if (++averagerPtr == averager.getNumChannels())
					averagerPtr = 1;

				newDataAvailable = true;
			}

			if (abstractFifo.getNumReady() < fft.getSize())
				waitForData.wait(100);
		}
	}

	void createPath(Path& p, const juce::Rectangle<float> bounds, float minFreq)
	{
		p.clear();
		p.preallocateSpace(8 + averager.getNumSamples() * 3);

		ScopedLock lockForReading(pathCreationLock);
		const auto* fftData = averager.getReadPointer(0);
		const auto factor = bounds.getWidth() / 11.1f;
		//double factor =  (3 + std::log10(2.2)) * 10; //bounds.getWidth() / 10.f;


		//p.startNewSubPath(bounds.getX() + factor * indexToX(0, minFreq), binToY(fftData[0], bounds));
		//for (int i = 0; i < averager.getNumSamples(); ++i)
		//	p.lineTo(bounds.getX() + bounds.getWidth() * indexToX(i, minFreq) / factor, binToY(fftData[i], bounds));

		p.startNewSubPath(bounds.getX() + factor * indexToX(0, minFreq), binToY(fftData[0], bounds));
		for (int i = 0; i < averager.getNumSamples(); ++i)
			p.lineTo(bounds.getX() + factor * indexToX(i, minFreq), binToY(fftData[i], bounds));

	}

	bool checkForNewData()
	{
		auto available = newDataAvailable;
		newDataAvailable = false;
		return available;
	}

private:

	inline float indexToX(float index, float minFreq) const
	{
		const auto freq = (sampleRate * index) / fft.getSize();
		return (freq > 0.01f) ? std::log(freq / minFreq) / std::log(2.0f) : 0.0f;
	}

	inline float binToY(float bin, const juce::Rectangle<float> bounds) const
	{
		const float infinity = -80.0f;
		return jmap(Decibels::gainToDecibels(bin, infinity),
			infinity, 0.0f, bounds.getBottom(), bounds.getY());
	}


	Type sampleRate{};

	AbstractFifo abstractFifo;
	AudioBuffer<Type> audioFifo;
	AudioBuffer<float> fftBuffer;
	AudioBuffer<float> averager;
	int averagerPtr = 1;
	bool newDataAvailable = false;

	WaitableEvent waitForData;
	CriticalSection pathCreationLock;

	dsp::FFT fft;
	dsp::WindowingFunction<Type> windowing;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Analyser)

};
