/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "Analyser.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DSP.h"
#include "../Assets/MathFunctions.h"
#include <iostream>
#include <sstream>
#include <windows.h>

#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

String FilterTestAudioProcessor::paramFrequency1("paramFrequency1");
String FilterTestAudioProcessor::paramResonance1("paramResonance1");
String FilterTestAudioProcessor::paramGain1("paramGain1");
String FilterTestAudioProcessor::paramFilterType1("paramFilterType1");
String FilterTestAudioProcessor::paramOversampling1("paramOversampling1");

String FilterTestAudioProcessor::paramFrequency2("paramFrequency2");
String FilterTestAudioProcessor::paramResonance2("paramResonance2");
String FilterTestAudioProcessor::paramGain2("paramGain2");
String FilterTestAudioProcessor::paramFilterType2("paramFilterType2");
String FilterTestAudioProcessor::paramOversampling2("paramOversampling2");

String FilterTestAudioProcessor::paramFrequency3("paramFrequency3");
String FilterTestAudioProcessor::paramResonance3("paramResonance3");
String FilterTestAudioProcessor::paramGain3("paramGain3");
String FilterTestAudioProcessor::paramFilterType3("paramFilterType3");
String FilterTestAudioProcessor::paramOversampling3("paramOversampling3");

String FilterTestAudioProcessor::paramFrequency4("paramFrequency4");
String FilterTestAudioProcessor::paramResonance4("paramResonance4");
String FilterTestAudioProcessor::paramGain4("paramGain4");
String FilterTestAudioProcessor::paramFilterType4("paramFilterType4");
String FilterTestAudioProcessor::paramOversampling4("paramOversampling4");

String FilterTestAudioProcessor::paramFrequency5("paramFrequency5");
String FilterTestAudioProcessor::paramResonance5("paramResonance5");
String FilterTestAudioProcessor::paramGain5("paramGain5");
String FilterTestAudioProcessor::paramFilterType5("paramFilterType5");
String FilterTestAudioProcessor::paramOversampling5("paramOversampling5");

String FilterTestAudioProcessor::paramFrequency6("paramFrequency6");
String FilterTestAudioProcessor::paramResonance6("paramResonance6");
String FilterTestAudioProcessor::paramGain6("paramGain6");
String FilterTestAudioProcessor::paramFilterType6("paramFilterType6");
String FilterTestAudioProcessor::paramOversampling6("paramOversampling6");

String FilterTestAudioProcessor::paramFilter1Button("paramFilter1Button");
String FilterTestAudioProcessor::paramFilter2Button("paramFilter2Button");
String FilterTestAudioProcessor::paramFilter3Button("paramFilter3Button");
String FilterTestAudioProcessor::paramFilter4Button("paramFilter4Button");
String FilterTestAudioProcessor::paramFilter5Button("paramFilter5Button");
String FilterTestAudioProcessor::paramFilter6Button("paramFilter6Button");

namespace IDs
{
	String editor {"editor"};
	String sizeX  {"size-x" };
	String sizeY  { "size-y" };
}
//paramFilterType(1),
//==============================================================================
FilterTestAudioProcessor::FilterTestAudioProcessor()
	: dspFrequency(18000.f), 
#ifndef JucePlugin_PreferredChannelConfigurations
      AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif

{
	undoManager = new UndoManager();
	state = new AudioProcessorValueTreeState(*this, undoManager);

	state->createAndAddParameter(paramFrequency1, "frequency1", TRANS("frequency1"), NormalisableRange <float>(10.0f, 22000.0f, 0.01f), 1000.0f, nullptr, nullptr);
	state->createAndAddParameter(paramResonance1, "resonance1", TRANS("resonance1"), NormalisableRange<float>(0.01f, 100.0f, 0.01f), 0.7071068f, nullptr, nullptr);
	state->createAndAddParameter(paramGain1, "gain1", TRANS("gain1"), NormalisableRange<float>(-40.0f, 40.0f, 0.01f), 1.0f, nullptr, nullptr);
	state->createAndAddParameter(paramFilterType1, "filter type1", TRANS("filter type1"), NormalisableRange<float>(0, 10, 1), 0, nullptr, nullptr); 
	state->createAndAddParameter(paramOversampling1, "oversampling1", TRANS("oversampling1"), NormalisableRange<float>(1, 4, 3), 1, nullptr, nullptr);
	state->addParameterListener(paramFrequency1, this);
	state->addParameterListener(paramResonance1, this);
	state->addParameterListener(paramGain1, this);
	state->addParameterListener(paramFilterType1, this);
	state->addParameterListener(paramOversampling1, this);

	state->createAndAddParameter(paramFrequency2, "frequency2", TRANS("frequency2"), NormalisableRange <float>(10.0f, 22000.0f, 0.01f), 1000.0f, nullptr, nullptr);
	state->createAndAddParameter(paramResonance2, "resonance2", TRANS("resonance2"), NormalisableRange<float>(0.01f, 100.0f, 0.01f), 0.7071068f, nullptr, nullptr);
	state->createAndAddParameter(paramGain2, "gain2", TRANS("gain2"), NormalisableRange<float>(-40.0f, 40.0f, 0.01f), 1.0f, nullptr, nullptr);
	state->createAndAddParameter(paramFilterType2, "filter type2", TRANS("filter type2"), NormalisableRange<float>(0, 10, 1), 10, nullptr, nullptr);
	state->createAndAddParameter(paramOversampling2, "oversampling", TRANS("oversampling"), NormalisableRange<float>(1, 4, 3), 1, nullptr, nullptr);
	state->addParameterListener(paramFrequency2, this);
	state->addParameterListener(paramResonance2, this);
	state->addParameterListener(paramGain2, this);
	state->addParameterListener(paramFilterType2, this);
	state->addParameterListener(paramOversampling2, this);

	state->createAndAddParameter(paramFrequency3, "frequency3", TRANS("frequency3"), NormalisableRange <float>(10.0f, 22000.0f, 0.01f), 1000.0f, nullptr, nullptr);
	state->createAndAddParameter(paramResonance3, "resonance3", TRANS("resonance3"), NormalisableRange<float>(0.01f, 100.0f, 0.01f), 0.7071068f, nullptr, nullptr);
	state->createAndAddParameter(paramGain3, "gain3", TRANS("gain3"), NormalisableRange<float>(-40.0f, 40.0f, 0.01f), 1.0f, nullptr, nullptr);
	state->createAndAddParameter(paramFilterType3, "filter type3", TRANS("filter type3"), NormalisableRange<float>(0, 10, 1), 10, nullptr, nullptr);
	state->createAndAddParameter(paramOversampling3, "oversampling3", TRANS("oversampling3"), NormalisableRange<float>(1, 4, 3), 1, nullptr, nullptr);
	state->addParameterListener(paramFrequency3, this);
	state->addParameterListener(paramResonance3, this);
	state->addParameterListener(paramGain3, this);
	state->addParameterListener(paramFilterType3, this);
	state->addParameterListener(paramOversampling3, this);

	state->createAndAddParameter(paramFrequency4, "frequency4", TRANS("frequency4"), NormalisableRange <float>(10.0f, 22000.0f, 0.01f), 1000.0f, nullptr, nullptr);
	state->createAndAddParameter(paramResonance4, "resonance4", TRANS("resonance4"), NormalisableRange<float>(0.01f, 100.0f, 0.01f), 0.7071068f, nullptr, nullptr);
	state->createAndAddParameter(paramGain4, "gain4", TRANS("gain4"), NormalisableRange<float>(-40.0f, 40.0f, 0.01f), 1.0f, nullptr, nullptr);
	state->createAndAddParameter(paramFilterType4, "filter type4", TRANS("filter type4"), NormalisableRange<float>(0, 10, 1), 10, nullptr, nullptr);
	state->createAndAddParameter(paramOversampling4, "oversampling4", TRANS("oversampling4"), NormalisableRange<float>(1, 4, 3), 1, nullptr, nullptr);
	state->addParameterListener(paramFrequency4, this);
	state->addParameterListener(paramResonance4, this);
	state->addParameterListener(paramGain4, this);
	state->addParameterListener(paramFilterType4, this);
	state->addParameterListener(paramOversampling4, this);

	state->createAndAddParameter(paramFrequency5, "frequency5", TRANS("frequency5"), NormalisableRange <float>(10.0f, 22000.0f, 0.01f), 1000.0f, nullptr, nullptr);
	state->createAndAddParameter(paramResonance5, "resonance5", TRANS("resonance5"), NormalisableRange<float>(0.01f, 100.0f, 0.01f), 0.7071068f, nullptr, nullptr);
	state->createAndAddParameter(paramGain5, "gain5", TRANS("gain5"), NormalisableRange<float>(-40.0f, 40.0f, 0.01f), 1.0f, nullptr, nullptr);
	state->createAndAddParameter(paramFilterType5, "filter type5", TRANS("filter type5"), NormalisableRange<float>(0, 10, 1), 10, nullptr, nullptr);
	state->createAndAddParameter(paramOversampling5, "oversampling5", TRANS("oversampling5"), NormalisableRange<float>(1, 4, 3), 1, nullptr, nullptr);
	state->addParameterListener(paramFrequency5, this);
	state->addParameterListener(paramResonance5, this);
	state->addParameterListener(paramGain5, this);
	state->addParameterListener(paramFilterType5, this);
	state->addParameterListener(paramOversampling5, this);

	state->createAndAddParameter(paramFrequency6, "frequency6", TRANS("frequency6"), NormalisableRange <float>(10.0f, 22000.0f, 0.01f), 1000.0f, nullptr, nullptr);
	state->createAndAddParameter(paramResonance6, "resonance6", TRANS("resonance6"), NormalisableRange<float>(0.01f, 100.0f, 0.01f), 0.7071068f, nullptr, nullptr);
	state->createAndAddParameter(paramGain6, "gain6", TRANS("gain6"), NormalisableRange<float>(-40.0f, 40.0f, 0.01f), 1.0f, nullptr, nullptr);
	state->createAndAddParameter(paramFilterType6, "filter type6", TRANS("filter type6"), NormalisableRange<float>(0, 10, 1), 10, nullptr, nullptr);
	state->createAndAddParameter(paramOversampling6, "oversampling6", TRANS("oversampling6"), NormalisableRange<float>(1, 4, 3), 1, nullptr, nullptr);
	state->addParameterListener(paramFrequency6, this);
	state->addParameterListener(paramResonance6, this);
	state->addParameterListener(paramGain6, this);
	state->addParameterListener(paramFilterType6, this);
	state->addParameterListener(paramOversampling6, this);

	//state->createAndAddParameter(paramFilter1Button, "filterButton1", TRANS("filterButton1"), NormalisableRange <float>(0, 1, 1), 1, nullptr, nullptr);
	//state->createAndAddParameter(paramFilter2Button, "filterButton2", TRANS("filterButton2"), NormalisableRange <float>(0, 1, 1), 0, nullptr, nullptr);
	//state->createAndAddParameter(paramFilter3Button, "filterButton3", TRANS("filterButton3"), NormalisableRange <float>(0, 1, 1), 0, nullptr, nullptr);
	//state->createAndAddParameter(paramFilter4Button, "filterButton4", TRANS("filterButton4"), NormalisableRange <float>(0, 1, 1), 0, nullptr, nullptr);
	//state->createAndAddParameter(paramFilter5Button, "filterButton5", TRANS("filterButton5"), NormalisableRange <float>(0, 1, 1), 0, nullptr, nullptr);
	//state->createAndAddParameter(paramFilter6Button, "filterButton6", TRANS("filterButton6"), NormalisableRange <float>(0, 1, 1), 0, nullptr, nullptr);
	//state->addParameterListener(paramFilter1Button, this);
	//state->addParameterListener(paramFilter2Button, this);

	frequencies.resize(300);
	for (size_t i = 0; i < frequencies.size(); ++i) {
		frequencies[i] = jmaplintolog(i / (frequencies.size() - 0.0), 10.0, 22000.0);
		//frequencies[i] = 20.0 * std::pow(2.0, i / 30.0);
	}
	magnitudes.resize(frequencies.size());
	
	bands.resize(7);
	for (int i = 0; i < getNumBands(); i++) {
		bands[i].magnitudes.resize(frequencies.size(), 1.0);
	}

	{
		auto& band = bands[0];
		band.name		= "Highest";
		band.colour		= Colours::gold;
		band.frequency	= 1000.0f;
		band.quality	= 0.707f;
		band.gain		= 1.0f;
		band.type		= LowPass;
	}
	{
		auto& band = bands[1];
	//	//band.name = "Highest";
		band.colour = Colours::silver;
	//	//band.frequency = 1000.0f;
	//	//band.quality = 0.707f;
	//	//band.gain = 1.0f;
		band.type = None;
	}
	{
		auto& band = bands[2];
		band.colour = Colours::cadetblue;
		band.type = None;
	}
	{
		auto& band = bands[3];
		band.colour = Colours::bisque;
		band.type = None;
	}
	{
		auto& band = bands[4];
		band.colour = Colours::blanchedalmond;
		band.type = None;
	}
	{
		auto& band = bands[5];
		band.colour = Colours::lavender;
		band.type = None;
	}

	updateBand(0);
	updateBand(1);
	updateBand(2);
	updateBand(3);
	updateBand(4);
	updateBand(5);
	state->state = ValueTree("Filter");

	oversampling.reset(new dsp::Oversampling<float>(2, 2, dsp::Oversampling<float>::filterHalfBandPolyphaseIIR, true));
}

FilterTestAudioProcessor::~FilterTestAudioProcessor()
{
	state = nullptr;
	undoManager = nullptr;
}

//==============================================================================
const String FilterTestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FilterTestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FilterTestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FilterTestAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FilterTestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FilterTestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FilterTestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FilterTestAudioProcessor::setCurrentProgram (int index)
{
}

const String FilterTestAudioProcessor::getProgramName (int index)
{
    return {};
}

void FilterTestAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FilterTestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	newSampleRate = sampleRate;

	dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = uint32(samplesPerBlock);
	spec.numChannels = uint32(getTotalNumOutputChannels());

	for (size_t i = 0; i < bands.size(); ++i) {
		updateBand(i);
	}

	oversampling->initProcessing(sampleRate);
	filter.get<6>().setGainLinear(1.0f);

	updatePlots();

	filter.prepare(spec);

	inputAnalyser.setupAnalyser(int(newSampleRate), float(newSampleRate));
	outputAnalyser.setupAnalyser(int(newSampleRate), float(newSampleRate));
	
}

void FilterTestAudioProcessor::releaseResources()
{
	inputAnalyser.stopThread(1000);
	outputAnalyser.stopThread(1000);
	//oversampling->reset();
}

void FilterTestAudioProcessor::parameterChanged(const String &parameterID, float newValue)
{
	for (size_t i = 0; i < bands.size(); ++i) {
		if (parameterID.endsWith("paramFrequency" + (String)(i + 1))) {
			bands[i].frequency = newValue;
			updateBand(i);
			updatePlots();
			return;
		}
		else if (parameterID.endsWith("Resonance" + (String)(i+1))) {
			bands[i].quality = newValue;
			updateBand(i);
			updatePlots();
			return;
		}
		else if (parameterID.endsWith("Gain" + (String)(i + 1))) {
			bands[i].gain = newValue;
			updateBand(i);
			updatePlots();
			return;
		}
		else if (parameterID.endsWith("FilterType" + (String)(i + 1))) {
			bands[i].type = (int)newValue;
			updateBand(i);
			updatePlots();
			return;
		}
		else if (parameterID.endsWith("Oversampling" + (String)(i + 1))) {
			samplingRateFactor = (int)newValue;
			updateBand(i);
			updatePlots();
			return;
		}
	}

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FilterTestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FilterTestAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	ignoreUnused(midiMessages);

	if (getActiveEditor() != nullptr)
		inputAnalyser.addAudioData(buffer, 0, getTotalNumInputChannels());
	
	dsp::AudioBlock<float> overBlock;
	dsp::AudioBlock<float> inoutBlock(buffer);

	if (samplingRateFactor == 4) // if oversampling is selected, process samples up
	{
		inoutBlock = inoutBlock.getSubBlock(0, buffer.getNumSamples());
		overBlock = oversampling->processSamplesUp(inoutBlock);
	}

	//if (bands[0].type < 4 ) { /*filter processing using juce DSP class*/
		
		if (samplingRateFactor != 4) // no oversampling
		{
			dsp::AudioBlock<float>	iobuffer(buffer);
			dsp::ProcessContextReplacing<float> context(iobuffer);
			filter.process(context);
		}
		else //oversampling
		{
			dsp::ProcessContextReplacing<float> context(overBlock);
			filter.process(context);
			oversampling->processSamplesDown(inoutBlock);
		}
	//}
	//else { /*manual filter processing*/

	//	if (samplingRateFactor != 4) // no oversampling
	//	{
	//		auto totalNumInputChannels = getTotalNumInputChannels();
	//		auto totalNumOutputChannels = getTotalNumOutputChannels();

	//		for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
	//			buffer.clear(i, 0, buffer.getNumSamples());

	//		for (int channel = 0; channel < totalNumInputChannels; ++channel)
	//		{
	//			float b0, b1, b2, a1, a2;
	//			dsp::IIR::Coefficients<float>::Ptr newCoefficients;
	//			newCoefficients = DSP::calculusCoefficients(bands[0].frequency, bands[0].quality, bands[0].gain, bands[0].type, newSampleRate, b0, b1, b2, a1, a2);

	//			auto* bufferWritePtr = buffer.getWritePointer(channel);
	//			auto v1 = theFilters[channel].v1;
	//			auto v2 = theFilters[channel].v2;

	//			for (int i = 0; i < buffer.getNumSamples(); i++)
	//			{
	//				//filtering

	//				auto cleansig = *bufferWritePtr;

	//				*bufferWritePtr = cleansig * b0 + v1;
	//				v1 = b1 * cleansig + v2 - a1 * *bufferWritePtr;
	//				v2 = b2 * cleansig - a2 * *bufferWritePtr;

	//				bufferWritePtr++;
	//			}
	//			theFilters[channel].v1 = v1;
	//			theFilters[channel].v2 = v2;
	//		}
	//	}
	//	else { // oversampling

	//		auto totalNumInputChannels = getTotalNumInputChannels();
	//		auto totalNumOutputChannels = getTotalNumOutputChannels();

	//		for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
	//			buffer.clear(i, 0, buffer.getNumSamples());

	//		for (int channel = 0; channel < totalNumInputChannels; ++channel)
	//		{
	//			float b0, b1, b2, a1, a2;
	//			dsp::IIR::Coefficients<float>::Ptr newCoefficients;
	//			newCoefficients = DSP::calculusCoefficients(bands[0].frequency, bands[0].quality, bands[0].gain, bands[0].type, newSampleRate * samplingRateFactor, b0, b1, b2, a1, a2);

	//			auto* bufferWritePtr = overBlock.getChannelPointer(channel);
	//			auto v1 = theFilters[channel].v1;
	//			auto v2 = theFilters[channel].v2;

	//			for (int i = 0; i < overBlock.getNumSamples(); i++)
	//			{
	//				//filtering

	//				auto cleansig = *bufferWritePtr;

	//				*bufferWritePtr = cleansig * b0 + v1;
	//				v1 = b1 * cleansig + v2 - a1 * *bufferWritePtr;
	//				v2 = b2 * cleansig - a2 * *bufferWritePtr;

	//				bufferWritePtr++;
	//			}
	//			theFilters[channel].v1 = v1;
	//			theFilters[channel].v2 = v2;
	//		}
	//		oversampling->processSamplesDown(inoutBlock);
	//	}

	//	//	auto totalNumInputChannels = getTotalNumInputChannels();
	//	//	auto totalNumOutputChannels = getTotalNumOutputChannels();
	//	//	//
	//	//for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
	//	//	buffer.clear(i, 0, buffer.getNumSamples());

	//	//	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	//	//	{
	//	//		float b0, b1, b2, a1, a2;
	//	//		dsp::IIR::Coefficients<float>::Ptr newCoefficients;
	//	//		newCoefficients = DSP::calculusCoefficients(bands[0].frequency, bands[0].quality, bands[0].gain, bands[0].type, newSampleRate * samplingRateFactor, b0, b1, b2, a1, a2);

	//	//		if (samplingRateFactor != 4) // no oversampling
	//	//		{
	//	//			auto* bufferWritePtr = buffer.getWritePointer(channel);
	//	//			auto v1 = theFilters[channel].v1;
	//	//			auto v2 = theFilters[channel].v2;

	//	//			for (int i = 0; i < buffer.getNumSamples(); i++)
	//	//			{
	//	//				//filtering

	//	//				auto cleansig = *bufferWritePtr;

	//	//				*bufferWritePtr = cleansig * b0 + v1;
	//	//				v1 = b1 * cleansig + v2 - a1 * *bufferWritePtr;
	//	//				v2 = b2 * cleansig - a2 * *bufferWritePtr;

	//	//				bufferWritePtr++;
	//	//			}
	//	//			theFilters[channel].v1 = v1;
	//	//			theFilters[channel].v2 = v2;
	//	//		}
	//	//		else // oversampling
	//	//		{
	//	//			auto* bufferWritePtr = overBlock.getChannelPointer(channel);
	//	//			auto v1 = theFilters[channel].v1;
	//	//			auto v2 = theFilters[channel].v2;

	//	//			for (int i = 0; i < overBlock.getNumSamples(); i++)
	//	//			{
	//	//				//filtering

	//	//				auto cleansig = *bufferWritePtr;

	//	//				*bufferWritePtr = cleansig * b0 + v1;
	//	//				v1 = b1 * cleansig + v2 - a1 * *bufferWritePtr;
	//	//				v2 = b2 * cleansig - a2 * *bufferWritePtr;

	//	//				bufferWritePtr++;
	//	//			}
	//	//			theFilters[channel].v1 = v1;
	//	//			theFilters[channel].v2 = v2;
	//	//		}
	//	//	}
	//	//}
	//	//if (samplingRateFactor == 4)
	//	//	oversampling->processSamplesDown(inoutBlock);
	//}
	if (getActiveEditor() != nullptr)
		outputAnalyser.addAudioData(buffer, 0, getTotalNumOutputChannels());
}

AudioProcessorValueTreeState& FilterTestAudioProcessor::getValueTreeState()
{
	return *state;
}

//==============================================================================
bool FilterTestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FilterTestAudioProcessor::createEditor()
{
    return new FilterTestAudioProcessorEditor (*this);
}

//==============================================================================
void FilterTestAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	MemoryOutputStream stream(destData, false);
	state->state.writeToStream(stream);
}

void FilterTestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
	if (tree.isValid()) {
		state->state = tree;
	}
}

void FilterTestAudioProcessor::setSavedSize(const Point<int>& size)
{
	editorSize = size;
}

FilterTestAudioProcessor::Band* FilterTestAudioProcessor::getBand(const int index)
{
	if (isPositiveAndBelow(index, bands.size()))
		return &bands[size_t(index)];
	return nullptr;
}

String FilterTestAudioProcessor::getFilterTypeName(const FilterType type)
{
	switch (type) {
		case LowPass:		return	TRANS("Low Pass");
		case HighPass:		return	TRANS("High Pass");
		case LowPass1st:	return	TRANS("1st Order Low Pass");
		case HighPass1st:	return	TRANS("1st Order High Pass");
		case ManualLowPass:  return  TRANS("Manual Low Pass");
		case ManualHighPass:  return  TRANS("Manual High Pass");
		case ManualLowPass2nd: return TRANS("Manual Low Pass 2nd Order");
		case ManualHighPass2nd: return TRANS("Manual High Pass 2nd Order");
		case ManualBandpass: return TRANS("Manual Band Pass");
		case ManualPeak: return TRANS("Manual Peak");
		case None: return TRANS("None Selected");
		}
}

String FilterTestAudioProcessor::getSamplingSelection(const Oversampling type)
{
	switch (type) {
	case NoOversampling:		return	TRANS("No Oversampling");
	case OversamplingX4:		return	TRANS("Oversampling x 4");
	
	}
}

FilterTestAudioProcessor::coefficients FilterTestAudioProcessor::updateBand(const size_t index)
{
	if (newSampleRate > 0) {
		float b0, b1, b2, a0, a1, a2;
		dsp::IIR::Coefficients<float>::Ptr newCoefficients;
		
		switch (bands[index].type) {
			case 0: //LowPass
				newCoefficients = dsp::IIR::Coefficients<float>::makeLowPass(newSampleRate * samplingRateFactor, bands[index].frequency, bands[index].quality);
				break;
			case 1: //HighPass
				newCoefficients = dsp::IIR::Coefficients<float>::makeHighPass(newSampleRate * samplingRateFactor, bands[index].frequency, bands[index].quality);
				break;
			case 2: //LowPass 1st Order
				newCoefficients = dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(newSampleRate * samplingRateFactor, bands[index].frequency);
				break;
			case 3: //HighPass 1st Order
				newCoefficients = dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(newSampleRate * samplingRateFactor, bands[index].frequency);
				break;
			case 4: // LowPass Manual
				newCoefficients = DSP::calculusCoefficients(bands[index].frequency, 0, 0, bands[index].type, newSampleRate * samplingRateFactor, b0, b1, b2, a1, a2);
				break;
			case 5: // HighPass Manual
				newCoefficients = DSP::calculusCoefficients(bands[index].frequency, 0, 0, bands[index].type, newSampleRate * samplingRateFactor, b0, b1, b2, a1, a2);
				break;
			case 6: // LowPass 2nd Manual
				newCoefficients = DSP::calculusCoefficients(bands[index].frequency, bands[index].quality, 0, bands[index].type, newSampleRate * samplingRateFactor, b0, b1, b2, a1, a2);
				break;
			case 7: // HighPass 2nd Manual
				newCoefficients = DSP::calculusCoefficients(bands[index].frequency, bands[index].quality, 0, bands[index].type, newSampleRate * samplingRateFactor, b0, b1, b2, a1, a2);
				break;
			case 8: // BandPass Manual
				newCoefficients = DSP::calculusCoefficients(bands[index].frequency, bands[index].quality, 0, bands[index].type, newSampleRate * samplingRateFactor, b0, b1, b2, a1, a2);
				break;
			case 9: // Peak Manual
				newCoefficients = DSP::calculusCoefficients(bands[index].frequency, bands[index].quality, bands[index].gain, bands[index].type, newSampleRate * samplingRateFactor, b0, b1, b2, a1, a2);
				break;
			case 10: // None
				newCoefficients = DSP::calculusCoefficients(bands[index].frequency, bands[index].quality, bands[index].gain, bands[index].type, newSampleRate * samplingRateFactor, b0, b1, b2, a1, a2);;
				break;
		}
		if (newCoefficients)
		{
			{
				ScopedLock processLock(getCallbackLock());
				if (index == 0)
					*filter.get<0>().state = *newCoefficients;
				else if (index == 1)
					*filter.get<1>().state = *newCoefficients;
				else if (index == 2)
					*filter.get<2>().state = *newCoefficients;
				else if (index == 3)
					*filter.get<3>().state = *newCoefficients;
				else if (index == 4)
					*filter.get<4>().state = *newCoefficients;
				else if (index == 5)
					*filter.get<5>().state = *newCoefficients;
			}
			newCoefficients->getMagnitudeForFrequencyArray(frequencies.data(), bands[index].magnitudes.data(),
															frequencies.size(), newSampleRate * samplingRateFactor);

			/* updates magnitudes */
			for (int i = 0; i < magnitudes.size(); ++i) {
				if(bands[index].type < 4)
					bands[index].magnitudes[i] = Decibels::gainToDecibels((bands[index].magnitudes[i]));
				else {
					bands[index].magnitudes[i] = Decibels::gainToDecibels(DSP::getMagnitudeForFrequency(frequencies[i], newSampleRate * samplingRateFactor,
						b0, b1, b2, a1, a2));
				}
			}
		}
		updatePlots();

		//newerCoefficients = newCoefficients;

		//filterCoefficients.b0 = newCoefficients->coefficients[b0];
		//filterCoefficients.b1 = newCoefficients->coefficients[b1];
		//filterCoefficients.b2 = newCoefficients->coefficients[b2];
		//filterCoefficients.a0 = newCoefficients->coefficients[a0];
		//filterCoefficients.a1 = newCoefficients->coefficients[a1];
		//filterCoefficients.a2 = newCoefficients->coefficients[a2];

		return filterCoefficients;
	}
}

void FilterTestAudioProcessor::createFrequencyPlot(Path& p, const std::vector<double>& mags, const juce::Rectangle<int> bounds, float pixelsPerDouble)
{
	const auto factor = bounds.getWidth() / 10.0f;
	p.clear();
	p.preallocateSpace(26);

	p.startNewSubPath(bounds.getX(), roundToInt(bounds.getY() + bounds.getHeight() * (-(mags[0] - 40.0 )/ 120.0 )));//bounds.getX(), roundToInt(bounds.getCentreY() - pixelsPerDouble * std::log(mags[0]) / std::log(2))); // plotFrame.getX(), roundToInt(plotFrame.getCentreY() - (2.0f * plotFrame.getHeight() / graphBuffer.getSample(1, 0))));
	const double xFactor = static_cast<double> (bounds.getWidth()) / frequencies.size();

	for (size_t i = 0; i < frequencies.size(); i++)
	{
		p.lineTo(roundToInt(bounds.getX() + i * xFactor), bounds.getY() + bounds.getHeight() * (-(mags[i] - 40.0) / 120.0));
			//roundToInt(bounds.getCentreY() - pixelsPerDouble * std::log(mags[i]) / std::log(2))); 
		//DBOUT("frequency " << frequencies[i] << ", magnitude " << i << ": " << mags[i] << "\n");
	}
}

void FilterTestAudioProcessor::createAnalyserPlot(Path& p, const juce::Rectangle<int> bounds, float minFreq, bool input)
{
	if (input)
		inputAnalyser.createPath(p, bounds.toFloat(), minFreq);
	else
		outputAnalyser.createPath(p, bounds.toFloat(), minFreq);
}

bool FilterTestAudioProcessor::checkForNewAnalyserData()
{
	return inputAnalyser.checkForNewData() || outputAnalyser.checkForNewData();
}

void FilterTestAudioProcessor::updatePlots()
{
	//auto gain = filter.get<6>().getGainLinear();
	//std::fill(magnitudes.begin(), magnitudes.end(), gain);
	sendChangeMessage();

}

inline float FilterTestAudioProcessor::indexToX(float index, float minFreq) const
{
	const auto freq = (44100 * index) / 1024;
	return (freq > 0.01f) ? std::log(freq / minFreq) / std::log(2.0f) : 0.0f;
}

inline float FilterTestAudioProcessor::binToY(float bin, const juce::Rectangle<int> bounds) const
{
	const float infinity = -80.0f;
	return jmap(Decibels::gainToDecibels(bin, infinity),
		infinity, 0.0f, bounds.toFloat().getBottom(), bounds.toFloat().getY());
}

const std::vector<double>& FilterTestAudioProcessor::getMagnitudes(int i)
{
		return bands[i].magnitudes;
}

int FilterTestAudioProcessor::getNumBands() const
{
	return static_cast<int>(bands.size());
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FilterTestAudioProcessor();
}
