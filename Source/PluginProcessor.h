/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/

extern AudioBuffer<float> graphBuffer;

class FilterTestAudioProcessor  : public AudioProcessor, 
								  public AudioProcessorValueTreeState::Listener,
								  public ChangeBroadcaster
{
public:

	enum FilterType
	{
		LowPass = 0,
		HighPass,
		LowPass1st,
		HighPass1st,
		ManualLowPass,
		ManualHighPass,
		ManualLowPass2nd,
		ManualHighPass2nd,
		ManualBandpass,
		ManualPeak,
		None,
		LastFilterID
	};

	enum Oversampling
	{
		NoOversampling = 1,
		OversamplingX4 = 4, 
		LastSamplingID
	};

    //==============================================================================
    FilterTestAudioProcessor();
    ~FilterTestAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

	static String getFilterTypeName(const FilterType type);

	static String getSamplingSelection(const Oversampling type);

	int getNumBands() const;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

	const std::vector<double>& getMagnitudes(int i);
	void createFrequencyPlot(Path& p, const std::vector<double>& mags, const juce::Rectangle<int> bounds, float pixelsPerDouble);
	void createAnalyserPlot(Path& p, const juce::Rectangle<int> bounds, float minFreq, bool input);
	bool checkForNewAnalyserData();

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
	void FilterTestAudioProcessor::setSavedSize(const Point<int>& size);

	AudioProcessorValueTreeState& getValueTreeState();

	static String paramFrequency1;
	static String paramResonance1;
	static String paramGain1;
	static String paramFilterType1;
	static String paramOversampling1;

	static String paramFrequency2;
	static String paramResonance2;
	static String paramGain2;
	static String paramFilterType2;
	static String paramOversampling2;

	static String paramFrequency3;
	static String paramResonance3;
	static String paramGain3;
	static String paramFilterType3;
	static String paramOversampling3;

	static String paramFrequency4;
	static String paramResonance4;
	static String paramGain4;
	static String paramFilterType4;
	static String paramOversampling4;

	static String paramFrequency5;
	static String paramResonance5;
	static String paramGain5;
	static String paramFilterType5;
	static String paramOversampling5;

	static String paramFrequency6;
	static String paramResonance6;
	static String paramGain6;
	static String paramFilterType6;
	static String paramOversampling6;

	static String paramFilter1Button;
	static String paramFilter2Button;
	static String paramFilter3Button;
	static String paramFilter4Button;
	static String paramFilter5Button;
	static String paramFilter6Button;

	int filter1ButtonValue;

	void parameterChanged(const String & parameterId, float newValue);

	inline float indexToX(float index, float minFreq) const;

	inline float binToY(float bin, const juce::Rectangle<int> bounds) const;

	//==============================================================================
	struct Band {
		String		name;
		Colour		colour;
		int			type		= 0;
		float		frequency	= 1000.0f;
		float		quality     = 0.707f;
		float		gain		= 1.0f;
		bool		active		= true;
		std::vector<double>		magnitudes;

	};

	struct coefficients {
		float b0; float b1; float b2;
		float a0; float a1; float a2;
	};

	coefficients filterCoefficients;

	Band* getBand(const int index);

	dsp::IIR::Coefficients<float>::Ptr newerCoefficients;

private:

	//AudioBuffer<float> graphBuffer;

	FilterTestAudioProcessor::coefficients updateBand(const size_t index);

	ScopedPointer<AudioProcessorValueTreeState> state;
	ScopedPointer<UndoManager> undoManager;

	std::vector<Band> bands;

	Atomic<float> dspFrequency;

	//struct FilterCoefficients
	//{
	//	float b0, b1, b2;
	//	float a1, a2;
	//};

	struct FilterState
	{
		float v1, v2;
	};

	FilterState theFilters[2];

	void updatePlots();

	std::vector<double> frequencies;
	std::vector<double> magnitudes;

	double newSampleRate = 0;

	using FilterBand = dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>>;
	using Gain = dsp::Gain<float>;
	dsp::ProcessorChain<FilterBand, FilterBand, FilterBand, FilterBand, FilterBand, FilterBand, Gain> filter;

	Analyser <float> inputAnalyser;
	Analyser <float> outputAnalyser;

	ScopedPointer<dsp::Oversampling<float>> oversampling;

	int samplingRateFactor{ 1 };

	Point<int> editorSize = { 900, 500 };


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterTestAudioProcessor)
};
