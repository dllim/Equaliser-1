/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "Analyser.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../Assets/MathFunctions.h"
#include "DSP.h"
#include <iostream>
#include <sstream>
#include <windows.h>
#include <math.h>

static int   clickRadius = 4;
static float maxDB = 40.0f;

#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

//==============================================================================
FilterTestAudioProcessorEditor::FilterTestAudioProcessorEditor (FilterTestAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.


	frequencySlider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	resonanceSlider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	gainSlider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	frequencyLabel = new Label("", "Frequency");
	resonanceLabel = new Label("", "Resonance");
	gainLabel = new Label("", "Gain");
	filterType = new ComboBox("Filter Types");
	oversampling = new ComboBox("Oversampling Selector");
	cutOffType = new Label("", "Cutoff Type");
	//addFilterButton = new TextButton("Add Filter");

	frequency2Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	resonance2Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	gain2Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	frequency2Label = new Label("", "Frequency");
	resonance2Label = new Label("", "Resonance");
	gain2Label = new Label("", "Gain");
	filter2Type = new ComboBox("Filter Types");
	oversampling2 = new ComboBox("Oversampling Selector");
	cutOffType2 = new Label("", "Cutoff Type");

	frequency3Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	resonance3Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	gain3Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	frequency3Label = new Label("", "Frequency");
	resonance3Label = new Label("", "Resonance");
	gain3Label = new Label("", "Gain");
	filter3Type = new ComboBox("Filter Types");
	oversampling3 = new ComboBox("Oversampling Selector");
	cutOffType3 = new Label("", "Cutoff Type");

	frequency4Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	resonance4Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	gain4Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	frequency4Label = new Label("", "Frequency");
	resonance4Label = new Label("", "Resonance");
	gain4Label = new Label("", "Gain");
	filter4Type = new ComboBox("Filter Types");
	oversampling4 = new ComboBox("Oversampling Selector");
	cutOffType4 = new Label("", "Cutoff Type");

	frequency5Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	resonance5Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	gain5Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	frequency5Label = new Label("", "Frequency");
	resonance5Label = new Label("", "Resonance");
	gain5Label = new Label("", "Gain");
	filter5Type = new ComboBox("Filter Types");
	oversampling5 = new ComboBox("Oversampling Selector");
	cutOffType5 = new Label("", "Cutoff Type");

	frequency6Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	resonance6Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	gain6Slider = new Slider(Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
	frequency6Label = new Label("", "Frequency");
	resonance6Label = new Label("", "Resonance");
	gain6Label = new Label("", "Gain");
	filter6Type = new ComboBox("Filter Types");
	oversampling6 = new ComboBox("Oversampling Selector");
	cutOffType6 = new Label("", "Cutoff Type");

	filter1Button = new TextButton("1");
	filter2Button = new TextButton("2");
	filter3Button = new TextButton("3");
	filter4Button = new TextButton("4");
	filter5Button = new TextButton("5");
	filter6Button = new TextButton("6");

	for (int i = 0; i < processor.getNumBands(); ++i) {
		auto* bandEditor = bandEditors.add(new BandEditor(i, processor));
		addAndMakeVisible(bandEditor);
	}

	for (int i = 0; i < FilterTestAudioProcessor::LastFilterID; ++i) {
		//filterType->addItem(i, i + 1);
		filterType->addItem(FilterTestAudioProcessor::getFilterTypeName(static_cast<FilterTestAudioProcessor::FilterType>(i)), i + 1);
		filter2Type->addItem(FilterTestAudioProcessor::getFilterTypeName(static_cast<FilterTestAudioProcessor::FilterType>(i)), i + 1);
		filter3Type->addItem(FilterTestAudioProcessor::getFilterTypeName(static_cast<FilterTestAudioProcessor::FilterType>(i)), i + 1);
		filter4Type->addItem(FilterTestAudioProcessor::getFilterTypeName(static_cast<FilterTestAudioProcessor::FilterType>(i)), i + 1);
		filter5Type->addItem(FilterTestAudioProcessor::getFilterTypeName(static_cast<FilterTestAudioProcessor::FilterType>(i)), i + 1);
		filter6Type->addItem(FilterTestAudioProcessor::getFilterTypeName(static_cast<FilterTestAudioProcessor::FilterType>(i)), i + 1);
	}
	
	oversampling->addItem("Digital", 1);
	oversampling->addItem("Analog", 2);
	oversampling2->addItem("Digital", 1);
	oversampling2->addItem("Analog", 2);
	oversampling3->addItem("Digital", 1);
	oversampling3->addItem("Analog", 2);
	oversampling4->addItem("Digital", 1);
	oversampling4->addItem("Analog", 2);
	oversampling5->addItem("Digital", 1);
	oversampling5->addItem("Analog", 2);
	oversampling6->addItem("Digital", 1);
	oversampling6->addItem("Analog", 2);

	frequencyAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFrequency1, *frequencySlider);
	resonanceAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramResonance1, *resonanceSlider);
	gainAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramGain1, *gainSlider);
	filterTypeAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFilterType1, *filterType);
	oversamplingAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramOversampling1, *oversampling);

	frequency2Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFrequency2, *frequency2Slider);
	resonance2Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramResonance2, *resonance2Slider);
	gain2Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramGain2, *gain2Slider);
	filterType2Attachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFilterType2, *filter2Type);
	oversampling2Attachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramOversampling2, *oversampling2);

	frequency3Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFrequency3, *frequency3Slider);
	resonance3Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramResonance3, *resonance3Slider);
	gain3Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramGain3, *gain3Slider);
	filterType3Attachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFilterType3, *filter3Type);
	oversampling3Attachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramOversampling3, *oversampling3);

	frequency4Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFrequency4, *frequency4Slider);
	resonance4Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramResonance4, *resonance4Slider);
	gain4Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramGain4, *gain4Slider);
	filterType4Attachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFilterType4, *filter4Type);
	oversampling4Attachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramOversampling4, *oversampling4);

	frequency5Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFrequency5, *frequency5Slider);
	resonance5Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramResonance5, *resonance5Slider);
	gain5Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramGain5, *gain5Slider);
	filterType5Attachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFilterType5, *filter5Type);
	oversampling5Attachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramOversampling5, *oversampling5);

	frequency6Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFrequency6, *frequency6Slider);
	resonance6Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramResonance6, *resonance6Slider);
	gain6Attachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramGain6, *gain6Slider);
	filterType6Attachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFilterType6, *filter6Type);
	oversampling6Attachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramOversampling6, *oversampling6);

	/*button1Attachment = new AudioProcessorValueTreeState::ButtonAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFilter1Button, *filter1Button);
	button2Attachment = new AudioProcessorValueTreeState::ButtonAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFilter2Button, *filter2Button);
	button3Attachment = new AudioProcessorValueTreeState::ButtonAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFilter3Button, *filter3Button);
	button4Attachment = new AudioProcessorValueTreeState::ButtonAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFilter4Button, *filter4Button);
	button5Attachment = new AudioProcessorValueTreeState::ButtonAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFilter5Button, *filter5Button);
	button6Attachment = new AudioProcessorValueTreeState::ButtonAttachment(p.getValueTreeState(), FilterTestAudioProcessor::paramFilter6Button, *filter6Button);*/

	addAndMakeVisible(frequencySlider);
	frequencySlider->setRange(10, 22000.0);
	frequencySlider->setSkewFactorFromMidPoint(600);

	addAndMakeVisible(resonanceSlider);
	resonanceSlider->setRange(0.01, 100.0);
	resonanceSlider->setSkewFactorFromMidPoint(0.1);

	addAndMakeVisible(gainSlider);
	gainSlider->setRange(-40.0, 40.0);
	gainSlider->setSkewFactorFromMidPoint(0.0);

	addAndMakeVisible(frequencyLabel);
	frequencyLabel->setJustificationType(Justification::centred);
	frequencyLabel->attachToComponent(frequencySlider, false);

	addAndMakeVisible(resonanceLabel);
	resonanceLabel->setJustificationType(Justification::centred);
	resonanceLabel->attachToComponent(resonanceSlider, false);

	addAndMakeVisible(gainLabel);
	gainLabel->setJustificationType(Justification::centred);
	gainLabel->attachToComponent(gainSlider, false);

	addAndMakeVisible(filterType);
	addAndMakeVisible(oversampling);

	addAndMakeVisible(cutOffType);

	// filter buttons
	addAndMakeVisible(filter1Button);
	filter1Button->setClickingTogglesState(true);
	filter1Button->setToggleState(true, true);
	filter1Button->setRadioGroupId(1, sendNotification);

	addAndMakeVisible(filter2Button);
	filter2Button->setClickingTogglesState(true);
	filter2Button->setRadioGroupId(1, sendNotification);

	addAndMakeVisible(filter3Button);
	filter3Button->setClickingTogglesState(true);
	filter3Button->setRadioGroupId(1, sendNotification);

	addAndMakeVisible(filter4Button);
	filter4Button->setClickingTogglesState(true);
	filter4Button->setRadioGroupId(1, sendNotification);

	addAndMakeVisible(filter5Button);
	filter5Button->setClickingTogglesState(true);
	filter5Button->setRadioGroupId(1, sendNotification);

	addAndMakeVisible(filter6Button);
	filter6Button->setClickingTogglesState(true);
	filter6Button->setRadioGroupId(1, sendNotification);

	// filter 2
	addAndMakeVisible(frequency2Slider);
	frequency2Slider->setRange(10, 22000.0);
	frequency2Slider->setSkewFactorFromMidPoint(600);

	addAndMakeVisible(resonance2Slider);
	resonance2Slider->setRange(0.01, 100.0);
	resonance2Slider->setSkewFactorFromMidPoint(0.1);

	addAndMakeVisible(gain2Slider);
	gain2Slider->setRange(-40.0, 40.0);
	gain2Slider->setSkewFactorFromMidPoint(0.0);

	addAndMakeVisible(frequency2Label);
	frequency2Label->setJustificationType(Justification::centred);
	frequency2Label->attachToComponent(frequency2Slider, false);

	addAndMakeVisible(resonance2Label);
	resonance2Label->setJustificationType(Justification::centred);
	resonance2Label->attachToComponent(resonance2Slider, false);

	addAndMakeVisible(gain2Label);
	gain2Label->setJustificationType(Justification::centred);
	gain2Label->attachToComponent(gain2Slider, false);

	addAndMakeVisible(filter2Type);
	addAndMakeVisible(oversampling2);

	addAndMakeVisible(cutOffType2);

	// filter 3
	addAndMakeVisible(frequency3Slider);
	frequency3Slider->setRange(10, 22000.0);
//	frequency3Slider->setSkewFactorFromMidPoint(600);

	addAndMakeVisible(resonance3Slider);
	resonance3Slider->setRange(0.01, 100.0);
	resonance3Slider->setSkewFactorFromMidPoint(0.1);

	addAndMakeVisible(gain3Slider);
	gain3Slider->setRange(-40.0, 40.0);
	gain3Slider->setSkewFactorFromMidPoint(0.0);

	addAndMakeVisible(frequency3Label);
	frequency3Label->setJustificationType(Justification::centred);
	frequency3Label->attachToComponent(frequency3Slider, false);

	addAndMakeVisible(resonance3Label);
	resonance3Label->setJustificationType(Justification::centred);
	resonance3Label->attachToComponent(resonance3Slider, false);

	addAndMakeVisible(gain3Label);
	gain3Label->setJustificationType(Justification::centred);
	gain3Label->attachToComponent(gain3Slider, false);

	addAndMakeVisible(filter3Type);
	addAndMakeVisible(oversampling3);

	addAndMakeVisible(cutOffType3);

	// filter 4
	addAndMakeVisible(frequency4Slider);
	frequency4Slider->setRange(10, 22000.0);
	frequency4Slider->setSkewFactorFromMidPoint(600);

	addAndMakeVisible(resonance4Slider);
	resonance4Slider->setRange(0.01, 100.0);
	resonance4Slider->setSkewFactorFromMidPoint(0.1);

	addAndMakeVisible(gain4Slider);
	gain4Slider->setRange(-40.0, 40.0);
	gain4Slider->setSkewFactorFromMidPoint(0.0);

	addAndMakeVisible(frequency4Label);
	frequency4Label->setJustificationType(Justification::centred);
	frequency4Label->attachToComponent(frequency4Slider, false);

	addAndMakeVisible(resonance4Label);
	resonance4Label->setJustificationType(Justification::centred);
	resonance4Label->attachToComponent(resonance4Slider, false);

	addAndMakeVisible(gain4Label);
	gain4Label->setJustificationType(Justification::centred);
	gain4Label->attachToComponent(gain4Slider, false);

	addAndMakeVisible(filter4Type);
	addAndMakeVisible(oversampling4);

	addAndMakeVisible(cutOffType4);

	// filter 2
	addAndMakeVisible(frequency5Slider);
	frequency5Slider->setRange(10, 22000.0);
	frequency5Slider->setSkewFactorFromMidPoint(600);

	addAndMakeVisible(resonance5Slider);
	resonance5Slider->setRange(0.01, 100.0);
	resonance5Slider->setSkewFactorFromMidPoint(0.1);

	addAndMakeVisible(gain5Slider);
	gain5Slider->setRange(-40.0, 40.0);
	gain5Slider->setSkewFactorFromMidPoint(0.0);

	addAndMakeVisible(frequency5Label);
	frequency5Label->setJustificationType(Justification::centred);
	frequency5Label->attachToComponent(frequency5Slider, false);

	addAndMakeVisible(resonance5Label);
	resonance5Label->setJustificationType(Justification::centred);
	resonance5Label->attachToComponent(resonance5Slider, false);

	addAndMakeVisible(gain5Label);
	gain5Label->setJustificationType(Justification::centred);
	gain5Label->attachToComponent(gain5Slider, false);

	addAndMakeVisible(filter5Type);
	addAndMakeVisible(oversampling5);

	addAndMakeVisible(cutOffType5);

	// filter 2
	addAndMakeVisible(frequency6Slider);
	frequency6Slider->setRange(10, 22000.0);
	frequency6Slider->setSkewFactorFromMidPoint(600);

	addAndMakeVisible(resonance6Slider);
	resonance6Slider->setRange(0.01, 100.0);
	resonance6Slider->setSkewFactorFromMidPoint(0.1);

	addAndMakeVisible(gain6Slider);
	gain6Slider->setRange(-40.0, 40.0);
	gain6Slider->setSkewFactorFromMidPoint(0.0);

	addAndMakeVisible(frequency6Label);
	frequency6Label->setJustificationType(Justification::centred);
	frequency6Label->attachToComponent(frequency6Slider, false);

	addAndMakeVisible(resonance6Label);
	resonance6Label->setJustificationType(Justification::centred);
	resonance6Label->attachToComponent(resonance6Slider, false);

	addAndMakeVisible(gain6Label);
	gain6Label->setJustificationType(Justification::centred);
	gain6Label->attachToComponent(gain6Slider, false);

	addAndMakeVisible(filter6Type);
	addAndMakeVisible(oversampling6);

	addAndMakeVisible(cutOffType6);

	updateFrequencyResponses();

#ifdef JUCE_OPENGL
	openGLContext.attachTo(*getTopLevelComponent());
#endif

	updateVisibility();
	processor.addChangeListener(this);
	startTimerHz(20);
    setSize (800, 600);
}

FilterTestAudioProcessorEditor::~FilterTestAudioProcessorEditor()
{
	processor.removeChangeListener(this);
	//frequencySlider = nullptr;
	//frequencyAttachment = nullptr;
	//thePlotComponent = nullptr;
	//frequencyLabel = nullptr;
}

//==============================================================================
void FilterTestAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);

	Graphics::ScopedSaveState state(g);

	g.setFont(12.0f);
	g.setColour(Colours::silver);
	g.drawRoundedRectangle(plotFrame.toFloat(), 5, 2);

	for (int i = 2; i < 33; ++i) {
		double x;
		double totalLength = (3 + std::log10(2.2)) * 10;
		g.setColour(Colours::silver.withAlpha(0.3f));
	
			
		if (i != 11 && i != 21 && i != 31 && i != 10 && i != 20 && i != 30)
			x = plotFrame.getX() +		plotFrame.getWidth() * ((std::log10(i % 10) * 10 + (floor(i / 10) * 10)) / totalLength);
		if (i == 10 || i == 20 || i == 30)
			x = plotFrame.getX() +		(plotFrame.getWidth() *	( i  / totalLength));
			//auto x = plotFrame.getX() + plotFrame.getWidth() * i * 0.1f;
		/*if (i == 33)
			x = plotFrame.getX() + (plotFrame.getWidth()	*	  ((std::log10(2.2) + 3) * 10 / totalLength));*/
		if (i > 0) g.drawVerticalLine(roundToInt(x), plotFrame.getY(), plotFrame.getBottom());
		g.setColour(Colours::silver);
		int freq;				//jmaplintolog(i / (10.0 - 1.0), 10.0, 22000.0);  //20.0f * std::pow(2.0f, (i * 0.1f) * 10.0f);
		if (i < 11)
			freq = i * 10;
		else if (i < 21)
			freq = (i - 10) * 100;
		else if (i < 31)
			freq = (i - 20) * 1000;
		else if (i < 41)
			freq = (i - 30) * 10000;
		if (freq == 20 || freq == 30 || freq == 50 || freq == 100 || freq == 200 || freq == 300 || freq == 500 || freq == 1000 || freq == 2000 || freq == 3000 || freq == 5000 || freq == 10000 || freq == 20000)
		{
			g.drawFittedText((freq < 1000) ? String(freq) + " Hz" : String(freq / 1000) + " kHz",
				roundToInt(x + 3), plotFrame.getBottom() - 18, 50, 15, Justification::left, 1);
		}

	}
	

	g.setColour(Colours::silver.withAlpha(0.3f));
	g.drawHorizontalLine(roundToInt(plotFrame.getY() + 0.125 * plotFrame.getHeight()), plotFrame.getX(), plotFrame.getRight());
	g.drawHorizontalLine(roundToInt(plotFrame.getY() + 0.25 * plotFrame.getHeight()), plotFrame.getX(), plotFrame.getRight());
	g.drawHorizontalLine(roundToInt(plotFrame.getY() + 0.375 * plotFrame.getHeight()), plotFrame.getX(), plotFrame.getRight());
	g.drawHorizontalLine(roundToInt(plotFrame.getY() + 0.5 * plotFrame.getHeight()), plotFrame.getX(), plotFrame.getRight());
	g.drawHorizontalLine(roundToInt(plotFrame.getY() + 0.625 * plotFrame.getHeight()), plotFrame.getX(), plotFrame.getRight());
	g.drawHorizontalLine(roundToInt(plotFrame.getY() + 0.75 * plotFrame.getHeight()), plotFrame.getX(), plotFrame.getRight());
	g.drawHorizontalLine(roundToInt(plotFrame.getY() + 0.875 * plotFrame.getHeight()), plotFrame.getX(), plotFrame.getRight());

	g.setColour(Colours::silver);
	//40dB
	g.drawFittedText(String(maxDB) + " dB", plotFrame.getX() + 3, plotFrame.getY() + 2, 50, 14, Justification::left, 1);
	//30dB
	//20dB
	//g.drawFittedText(String(maxDB / 2) + " dB", plotFrame.getX() + 3, roundToInt(plotFrame.getY() + 2 + 0.25 * plotFrame.getHeight()), 50, 14, Justification::left, 1);
	//10dB
	g.drawFittedText(String(maxDB / 4) + " dB", plotFrame.getX() + 3, roundToInt(plotFrame.getY() + 2 + 0.25 * plotFrame.getHeight()), 50, 14, Justification::left, 1);
	//0dB
	//g.drawFittedText(" 0 dB", plotFrame.getX() + 3, roundToInt(plotFrame.getY() + 2 + 0.5  * plotFrame.getHeight()), 50, 14, Justification::left, 1);
	//-10dB
	//-20dB (centre)
	g.drawFittedText(String(-maxDB / 2) + " dB", plotFrame.getX() + 3, roundToInt(plotFrame.getY() + 2 + 0.5 * plotFrame.getHeight()), 50, 14, Justification::left, 1);
	//-30dB
	//-40dB
	//g.drawFittedText(String(-maxDB) + " dB", plotFrame.getX() + 3, roundToInt(plotFrame.getY() + 2 + 0.75 * plotFrame.getHeight()), 50, 14, Justification::left, 1);
	//-50dB
	g.drawFittedText(String(-maxDB * 5 / 4) + " dB", plotFrame.getX() + 3, roundToInt(plotFrame.getY() + 2 + 0.75 * plotFrame.getHeight()), 50, 14, Justification::left, 1);
	//-60dB
	//-70dB
	//-80dB
	g.drawFittedText(String(-maxDB * 2) + " dB", plotFrame.getX() + 3, roundToInt(plotFrame.getY() + 2 + 1 * plotFrame.getHeight()), 50, 14, Justification::left, 1);

	g.reduceClipRegion(plotFrame);

	//input plot
	g.setFont(16.0f);
	processor.createAnalyserPlot(analyserPath, plotFrame, 10.0f, true);
	g.setColour(Colours::olive);
	//g.drawFittedText("Input Frequency Response", plotFrame.reduced(8), Justification::topRight, 1);
	g.strokePath(analyserPath, PathStrokeType(1.0));

	//output plot
	processor.createAnalyserPlot(analyserPathOutput, plotFrame, 10.0f, false);
	g.setColour(Colours::limegreen);
	//g.drawFittedText("Output Frequency Response", plotFrame.reduced(16), Justification::topRight, 1);
	g.strokePath(analyserPathOutput, PathStrokeType(1.0));

	for (int i = 0; i < processor.getNumBands(); i++) {
		
		auto* bandEditor = bandEditors.getUnchecked(i);
		auto* band = processor.getBand(i);
		if (band->type != 10) {
			auto pixelsPerDouble = 2.0f * plotFrame.getHeight() / Decibels::decibelsToGain(maxDB);

			processor.createFrequencyPlot(bandEditor->bandFrequencyResponse, processor.getMagnitudes(i), plotFrame, pixelsPerDouble);
			g.setColour(band->colour);
			//g.drawFittedText("Filter Frequency Response", plotFrame.reduced(24), Justification::topRight, 1);
			g.strokePath(bandEditor->bandFrequencyResponse, PathStrokeType(1.0));
		}
	}

	updateVisibility();
}

void FilterTestAudioProcessorEditor::resized()
{
	// Filter 1
	juce::Rectangle<int> freqbox(getLocalBounds());
	freqbox.setWidth(getWidth() / 8);
	freqbox.setHeight(getHeight() / 6);
	freqbox.translate(0, 400);
	frequencySlider->setBounds(freqbox);

	juce::Rectangle<int> resbox(getLocalBounds());
	resbox.setWidth(getWidth() / 8);
	resbox.setHeight(getHeight() / 6);
	resbox.translate(100, 400);
	resonanceSlider->setBounds(resbox);

	juce::Rectangle<int> gainbox(getLocalBounds());
	gainbox.setWidth(getWidth() / 8);
	gainbox.setHeight(getHeight() / 6);
	gainbox.translate(200, 400);
	gainSlider->setBounds(gainbox);

	juce::Rectangle<int> filterTypebox(getLocalBounds());
	filterTypebox.setWidth(getWidth() / 6);
	filterTypebox.setHeight(getHeight() / 24);
	filterTypebox.translate(350, 400);
	filterType->setBounds(filterTypebox);

	juce::Rectangle<int> oversamplingbox(getLocalBounds());
	oversamplingbox.setWidth(getWidth() / 6);
	oversamplingbox.setHeight(getHeight() / 24);
	oversamplingbox.translate(350, 470);
	oversampling->setBounds(oversamplingbox);

	juce::Rectangle<int>cutOfftextbox(getLocalBounds());
	cutOfftextbox.setWidth(getWidth() / 6);
	cutOfftextbox.setHeight(getHeight() / 24);
	cutOfftextbox.translate(350, 440);
	cutOffType->setBounds(cutOfftextbox);

	// Filter 2
	juce::Rectangle<int> freqbox2(getLocalBounds());
	freqbox2.setWidth(getWidth() / 8);
	freqbox2.setHeight(getHeight() / 6);
	freqbox2.translate(0, 400);
	frequency2Slider->setBounds(freqbox2);

	juce::Rectangle<int> resbox2(getLocalBounds());
	resbox2.setWidth(getWidth() / 8);
	resbox2.setHeight(getHeight() / 6);
	resbox2.translate(100, 400);
	resonance2Slider->setBounds(resbox2);

	juce::Rectangle<int> gainbox2(getLocalBounds());
	gainbox2.setWidth(getWidth() / 8);
	gainbox2.setHeight(getHeight() / 6);
	gainbox2.translate(200,400);
	gain2Slider->setBounds(gainbox2);

	juce::Rectangle<int> filterTypebox2(getLocalBounds());
	filterTypebox2.setWidth(getWidth() / 6);
	filterTypebox2.setHeight(getHeight() / 24);
	filterTypebox2.translate(350, 400);
	filter2Type->setBounds(filterTypebox2);

	juce::Rectangle<int> oversamplingbox2(getLocalBounds());
	oversamplingbox2.setWidth(getWidth() / 6);
	oversamplingbox2.setHeight(getHeight() / 24);
	oversamplingbox2.translate(350, 470);
	oversampling2->setBounds(oversamplingbox2);

	juce::Rectangle<int>cutOfftextbox2(getLocalBounds());
	cutOfftextbox2.setWidth(getWidth() / 6);
	cutOfftextbox2.setHeight(getHeight() / 24);
	cutOfftextbox2.translate(350, 440);
	cutOffType2->setBounds(cutOfftextbox2);

	// Filter 3
	juce::Rectangle<int> freqbox3(getLocalBounds());
	freqbox3.setWidth(getWidth() / 8);
	freqbox3.setHeight(getHeight() / 6);
	freqbox3.translate(0, 400);
	frequency3Slider->setBounds(freqbox3);

	juce::Rectangle<int> resbox3(getLocalBounds());
	resbox3.setWidth(getWidth() / 8);
	resbox3.setHeight(getHeight() / 6);
	resbox3.translate(100, 400);
	resonance3Slider->setBounds(resbox3);

	juce::Rectangle<int> gainbox3(getLocalBounds());
	gainbox3.setWidth(getWidth() / 8);
	gainbox3.setHeight(getHeight() / 6);
	gainbox3.translate(200, 400);
	gain3Slider->setBounds(gainbox3);

	juce::Rectangle<int> filterTypebox3(getLocalBounds());
	filterTypebox3.setWidth(getWidth() / 6);
	filterTypebox3.setHeight(getHeight() / 24);
	filterTypebox3.translate(350, 400);
	filter3Type->setBounds(filterTypebox3);

	juce::Rectangle<int> oversamplingbox3(getLocalBounds());
	oversamplingbox3.setWidth(getWidth() / 6);
	oversamplingbox3.setHeight(getHeight() / 24);
	oversamplingbox3.translate(350, 470);
	oversampling3->setBounds(oversamplingbox3);

	juce::Rectangle<int>cutOfftextbox3(getLocalBounds());
	cutOfftextbox3.setWidth(getWidth() / 6);
	cutOfftextbox3.setHeight(getHeight() / 24);
	cutOfftextbox3.translate(350, 440);
	cutOffType3->setBounds(cutOfftextbox3);

	// Filter 4
	juce::Rectangle<int> freqbox4(getLocalBounds());
	freqbox4.setWidth(getWidth() / 8);
	freqbox4.setHeight(getHeight() / 6);
	freqbox4.translate(0, 400);
	frequency4Slider->setBounds(freqbox4);

	juce::Rectangle<int> resbox4(getLocalBounds());
	resbox4.setWidth(getWidth() / 8);
	resbox4.setHeight(getHeight() / 6);
	resbox4.translate(100, 400);
	resonance4Slider->setBounds(resbox4);

	juce::Rectangle<int> gainbox4(getLocalBounds());
	gainbox4.setWidth(getWidth() / 8);
	gainbox4.setHeight(getHeight() / 6);
	gainbox4.translate(200, 400);
	gain4Slider->setBounds(gainbox4);

	juce::Rectangle<int> filterTypebox4(getLocalBounds());
	filterTypebox4.setWidth(getWidth() / 6);
	filterTypebox4.setHeight(getHeight() / 24);
	filterTypebox4.translate(350, 400);
	filter4Type->setBounds(filterTypebox4);

	juce::Rectangle<int> oversamplingbox4(getLocalBounds());
	oversamplingbox4.setWidth(getWidth() / 6);
	oversamplingbox4.setHeight(getHeight() / 24);
	oversamplingbox4.translate(350, 470);
	oversampling4->setBounds(oversamplingbox4);

	juce::Rectangle<int>cutOfftextbox4(getLocalBounds());
	cutOfftextbox4.setWidth(getWidth() / 6);
	cutOfftextbox4.setHeight(getHeight() / 24);
	cutOfftextbox4.translate(350, 440);
	cutOffType4->setBounds(cutOfftextbox4);

	// Filter 5
	juce::Rectangle<int> freqbox5(getLocalBounds());
	freqbox5.setWidth(getWidth() / 8);
	freqbox5.setHeight(getHeight() / 6);
	freqbox5.translate(0, 400);
	frequency5Slider->setBounds(freqbox5);

	juce::Rectangle<int> resbox5(getLocalBounds());
	resbox5.setWidth(getWidth() / 8);
	resbox5.setHeight(getHeight() / 6);
	resbox5.translate(100, 400);
	resonance5Slider->setBounds(resbox5);

	juce::Rectangle<int> gainbox5(getLocalBounds());
	gainbox5.setWidth(getWidth() / 8);
	gainbox5.setHeight(getHeight() / 6);
	gainbox5.translate(200, 400);
	gain5Slider->setBounds(gainbox5);

	juce::Rectangle<int> filterTypebox5(getLocalBounds());
	filterTypebox5.setWidth(getWidth() / 6);
	filterTypebox5.setHeight(getHeight() / 24);
	filterTypebox5.translate(350, 400);
	filter5Type->setBounds(filterTypebox5);

	juce::Rectangle<int> oversamplingbox5(getLocalBounds());
	oversamplingbox5.setWidth(getWidth() / 6);
	oversamplingbox5.setHeight(getHeight() / 24);
	oversamplingbox5.translate(350, 470);
	oversampling5->setBounds(oversamplingbox5);

	juce::Rectangle<int>cutOfftextbox5(getLocalBounds());
	cutOfftextbox5.setWidth(getWidth() / 6);
	cutOfftextbox5.setHeight(getHeight() / 24);
	cutOfftextbox5.translate(350, 440);
	cutOffType5->setBounds(cutOfftextbox5);

	// Filter 6
	juce::Rectangle<int> freqbox6(getLocalBounds());
	freqbox6.setWidth(getWidth() / 8);
	freqbox6.setHeight(getHeight() / 6);
	freqbox6.translate(0, 400);
	frequency6Slider->setBounds(freqbox6);

	juce::Rectangle<int> resbox6(getLocalBounds());
	resbox6.setWidth(getWidth() / 8);
	resbox6.setHeight(getHeight() / 6);
	resbox6.translate(100, 400);
	resonance6Slider->setBounds(resbox6);

	juce::Rectangle<int> gainbox6(getLocalBounds());
	gainbox6.setWidth(getWidth() / 8);
	gainbox6.setHeight(getHeight() / 6);
	gainbox6.translate(200, 400);
	gain6Slider->setBounds(gainbox6);

	juce::Rectangle<int> filterTypebox6(getLocalBounds());
	filterTypebox6.setWidth(getWidth() / 6);
	filterTypebox6.setHeight(getHeight() / 24);
	filterTypebox6.translate(350, 400);
	filter6Type->setBounds(filterTypebox6);

	juce::Rectangle<int> oversamplingbox6(getLocalBounds());
	oversamplingbox6.setWidth(getWidth() / 6);
	oversamplingbox6.setHeight(getHeight() / 24);
	oversamplingbox6.translate(350, 470);
	oversampling6->setBounds(oversamplingbox6);

	juce::Rectangle<int>cutOfftextbox6(getLocalBounds());
	cutOfftextbox6.setWidth(getWidth() / 6);
	cutOfftextbox6.setHeight(getHeight() / 24);
	cutOfftextbox6.translate(350, 440);
	cutOffType6->setBounds(cutOfftextbox6);


	//juce::Rectangle<int>addFilterButtonBox(getLocalBounds());
	//addFilterButtonBox.setWidth(getWidth() / 6);
	//addFilterButtonBox.setHeight(getHeight() / 24);
	//addFilterButtonBox.translate(600, 350);
	//addFilterButton->setBounds(addFilterButtonBox);

	juce::Rectangle<int>filter1ButtonBox(getLocalBounds());
	filter1ButtonBox.setWidth(getWidth() / 24);
	filter1ButtonBox.setHeight(getHeight() / 24);
	filter1ButtonBox.translate(10, 325);
	filter1Button->setBounds(filter1ButtonBox);

	juce::Rectangle<int>filter2ButtonBox(getLocalBounds());
	filter2ButtonBox.setWidth(getWidth() / 24);
	filter2ButtonBox.setHeight(getHeight() / 24);
	filter2ButtonBox.translate(45, 325);
	filter2Button->setBounds(filter2ButtonBox);

	juce::Rectangle<int>filter3ButtonBox(getLocalBounds());
	filter3ButtonBox.setWidth(getWidth() / 24);
	filter3ButtonBox.setHeight(getHeight() / 24);
	filter3ButtonBox.translate(80, 325);
	filter3Button->setBounds(filter3ButtonBox);

	juce::Rectangle<int>filter4ButtonBox(getLocalBounds());
	filter4ButtonBox.setWidth(getWidth() / 24);
	filter4ButtonBox.setHeight(getHeight() / 24);
	filter4ButtonBox.translate(115, 325);
	filter4Button->setBounds(filter4ButtonBox);

	juce::Rectangle<int>filter5ButtonBox(getLocalBounds());
	filter5ButtonBox.setWidth(getWidth() / 24);
	filter5ButtonBox.setHeight(getHeight() / 24);
	filter5ButtonBox.translate(150, 325);
	filter5Button->setBounds(filter5ButtonBox);
	
	juce::Rectangle<int>filter6ButtonBox(getLocalBounds());
	filter6ButtonBox.setWidth(getWidth() / 24);
	filter6ButtonBox.setHeight(getHeight() / 24);
	filter6ButtonBox.translate(185, 325);
	filter6Button->setBounds(filter6ButtonBox);

	processor.setSavedSize({ getWidth(), getHeight() });
	plotFrame = getLocalBounds().reduced(3, 3);

	auto bandSpace = plotFrame.removeFromBottom(getHeight() / 2);

	plotFrame.reduce(3, 3);

	updateFrequencyResponses();
}

void FilterTestAudioProcessorEditor::changeListenerCallback(ChangeBroadcaster* sender)
{
	ignoreUnused(sender);
	updateFrequencyResponses();
	repaint();
}

void FilterTestAudioProcessorEditor::timerCallback()
{
	if (processor.checkForNewAnalyserData())
		repaint(plotFrame);
}

void FilterTestAudioProcessorEditor::updateFrequencyResponses() 
{
	auto pixelsPerDouble = 2.0f * plotFrame.getHeight() / Decibels::decibelsToGain(maxDB);

	for (int i = 0; i < bandEditors.size(); ++i) {
		auto* bandEditor = bandEditors.getUnchecked(i);
		if (auto* band = processor.getBand(i)) {
			bandEditor->updateControls(band->type);
			bandEditor->bandFrequencyResponse.clear();
			processor.createFrequencyPlot(bandEditor->bandFrequencyResponse, band->magnitudes, plotFrame.withX(plotFrame.getX() + 1), pixelsPerDouble);
		}
	}
	frequencyResponse.clear();
	processor.createFrequencyPlot(frequencyResponse, processor.getMagnitudes(0), plotFrame, pixelsPerDouble);
}

FilterTestAudioProcessorEditor::BandEditor::BandEditor(const int i, FilterTestAudioProcessor& p)
	: index (i),
	  processor (p),
	  frequency(Slider::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow)
{
	frame.setText("test");

	addAndMakeVisible(frequency);
	attachments.add(new AudioProcessorValueTreeState::SliderAttachment(processor.getValueTreeState(), FilterTestAudioProcessor::paramFrequency1, frequency));
	frequency.setSkewFactorFromMidPoint(1000.0);
	frequency.setTooltip(TRANS("Filter's frequency"));
}

void FilterTestAudioProcessorEditor::BandEditor::resized()
{
	auto bounds = getLocalBounds();
	frame.setBounds(bounds);

	bounds.reduce(10, 20);

	filterType.setBounds(bounds.removeFromTop(20));

	auto freqBounds = bounds.removeFromBottom(bounds.getHeight() * 2 / 3);
	frequency.setBounds(freqBounds.withTop(freqBounds.getY() + 10));
}

void FilterTestAudioProcessorEditor::BandEditor::updateControls(int type)
{
	switch (type) {
		case 0:// FilterTestAudioProcessor::LowPass:
			frequency.setEnabled(true);
			break;
		default:
			frequency.setEnabled(true);
			break;
	}
}

void FilterTestAudioProcessorEditor::BandEditor::setFrequency(float freq)
{
	frequency.setValue(freq, sendNotification);
}

inline float FilterTestAudioProcessorEditor::indexToX(float index, float minFreq) const
{
	const auto freq = (44100 * index) / 12;
	return (freq > 0.01f) ? std::log(freq / minFreq) / std::log(2.0f) : 0.0f;
}

inline float FilterTestAudioProcessorEditor::binToY(float bin, const juce::Rectangle<float> bounds) const
{
	const float infinity = -80.0f;
	return jmap((bin, infinity),
		infinity, 0.0f, bounds.getBottom(), bounds.getY());
}

void FilterTestAudioProcessorEditor::updateVisibility()
{
	auto type1 = filterType->getSelectedId() - 1;
	auto type2 = filter2Type->getSelectedId() - 1;
	auto type3 = filter3Type->getSelectedId() - 1;
	auto type4 = filter4Type->getSelectedId() - 1;
	auto type5 = filter5Type->getSelectedId() - 1;
	auto type6 = filter6Type->getSelectedId() - 1;

	auto button1ToggleState = filter1Button->getToggleState();
	auto button2ToggleState = filter2Button->getToggleState();
	auto button3ToggleState = filter3Button->getToggleState();
	auto button4ToggleState = filter4Button->getToggleState();
	auto button5ToggleState = filter5Button->getToggleState();
	auto button6ToggleState = filter6Button->getToggleState();

	//filter 1
	frequencyLabel->setEnabled(type1 != 10 && button1ToggleState == true);
	frequencySlider->setVisible(button1ToggleState == true);
	frequencySlider->setEnabled(type1 != 10 && button1ToggleState == true);

	resonanceLabel->setEnabled(type1 != 10 && button1ToggleState == true && (type1 > 5 || type1 < 2));
	resonanceSlider->setVisible(button1ToggleState == true);
	resonanceSlider->setEnabled(type1 != 10 && button1ToggleState == true && (type1 > 5 || type1 < 2));

	gainLabel->setEnabled(type1 != 10 && type1 == 9 && button1ToggleState == true);
	gainSlider->setVisible(button1ToggleState == true);
	gainSlider->setEnabled(type1 != 10 && type1 == 9 && button1ToggleState == true);

	filterType->setVisible(button1ToggleState == true);

	oversampling->setVisible(button1ToggleState == true);
	oversampling->setEnabled(type1 != 10 && button1ToggleState == true);
	cutOffType->setVisible(button1ToggleState == true);

	//filter 2
	frequency2Label->setEnabled(type2 != 10 && button2ToggleState == true);
	frequency2Slider->setVisible(button2ToggleState == true);
	frequency2Slider->setEnabled(type2 != 10 && button2ToggleState == true);

	resonance2Label->setEnabled(type2 != 10 && button2ToggleState == true && (type2 > 5 || type2 < 2));
	resonance2Slider->setVisible(button2ToggleState == true);
	resonance2Slider->setEnabled(type2 != 10 && button2ToggleState == true && (type2 > 5 || type2 < 2));

	gain2Label->setEnabled(type2 != 10 && type2 == 9 && button2ToggleState == true);
	gain2Slider->setVisible(button2ToggleState == true);
	gain2Slider->setEnabled(type2 != 10 && type2 == 9 && button2ToggleState == true);

	filter2Type->setVisible(button2ToggleState == true);

	oversampling2->setVisible(button2ToggleState == true);
	oversampling2->setEnabled(type2 != 10 && button2ToggleState == true);
	cutOffType2->setVisible(button2ToggleState == true);

	//filter 3
	frequency3Label->setEnabled(type3 != 10 && button3ToggleState == true);
	frequency3Slider->setVisible(button3ToggleState == true);
	frequency3Slider->setEnabled(type3 != 10 && button3ToggleState == true);

	resonance3Label->setEnabled(type3 != 10 && button3ToggleState == true && (type3 > 5 || type3 < 2));
	resonance3Slider->setVisible(button3ToggleState == true);
	resonance3Slider->setEnabled(type3 != 10 && button3ToggleState == true && (type3 > 5 || type3 < 2));

	gain3Label->setEnabled(type3 != 10 && type3 == 9 && button3ToggleState == true);
	gain3Slider->setVisible(button3ToggleState == true);
	gain3Slider->setEnabled(type3 != 10 && type3 == 9 && button3ToggleState == true);

	filter3Type->setVisible(button3ToggleState == true);

	oversampling3->setVisible(button3ToggleState == true);
	oversampling3->setEnabled(type3 != 10 && button3ToggleState == true);
	cutOffType3->setVisible(button3ToggleState == true);

	//filter 4
	frequency4Label->setEnabled(type4 != 10 && button4ToggleState == true);
	frequency4Slider->setVisible(button4ToggleState == true);
	frequency4Slider->setEnabled(type4 != 10 && button4ToggleState == true);

	resonance4Label->setEnabled(type4 != 10 && button4ToggleState == true && (type4 > 5 || type4 < 2));
	resonance4Slider->setVisible(button4ToggleState == true);
	resonance4Slider->setEnabled(type4 != 10 && button4ToggleState == true && (type4 > 5 || type4 < 2));

	gain4Label->setEnabled(type4 != 10 && type4 == 9 && button4ToggleState == true);
	gain4Slider->setVisible(button4ToggleState == true);
	gain4Slider->setEnabled(type4 != 10 && type4 == 9 && button4ToggleState == true);

	filter4Type->setVisible(button4ToggleState == true);

	oversampling4->setVisible(button4ToggleState == true);
	oversampling4->setEnabled(type4 != 10 && button4ToggleState == true);
	cutOffType4->setVisible(button4ToggleState == true);

	//filter 5
	frequency5Label->setEnabled(type5 != 10 && button5ToggleState == true);
	frequency5Slider->setVisible(button5ToggleState == true);
	frequency5Slider->setEnabled(type5 != 10 && button5ToggleState == true);

	resonance5Label->setEnabled(type5 != 10 && button5ToggleState == true && (type5 > 5 || type5 < 2));
	resonance5Slider->setVisible(button5ToggleState == true);
	resonance5Slider->setEnabled(type5 != 10 && button5ToggleState == true && (type5 > 5 || type5 < 2));

	gain5Label->setEnabled(type5 != 10 && type5 == 9 && button5ToggleState == true);
	gain5Slider->setVisible(button5ToggleState == true);
	gain5Slider->setEnabled(type5 != 10 && type5 == 9 && button5ToggleState == true);

	filter5Type->setVisible(button5ToggleState == true);

	oversampling5->setVisible(button5ToggleState == true);
	oversampling5->setEnabled(type5 != 10 && button5ToggleState == true);
	cutOffType5->setVisible(button5ToggleState == true);

	//filter 6
	frequency6Label->setEnabled(type6 != 10 && button6ToggleState == true);
	frequency6Slider->setVisible(button6ToggleState == true);
	frequency6Slider->setEnabled(type6 != 10 && button6ToggleState == true);

	resonance6Label->setEnabled(type6 != 10 && button6ToggleState == true && (type6 > 5 || type6 < 2));
	resonance6Slider->setVisible(button6ToggleState == true);
	resonance6Slider->setEnabled(type6 != 10 && button6ToggleState == true && (type6 > 5 || type6 < 2));

	gain6Label->setEnabled(type6 != 10 && type6 == 9 && button6ToggleState == true);
	gain6Slider->setVisible(button6ToggleState == true);
	gain6Slider->setEnabled(type6 != 10 && type6 == 9 && button6ToggleState == true);

	filter6Type->setVisible(button6ToggleState == true);

	oversampling6->setVisible(button6ToggleState == true);
	oversampling6->setEnabled(type6 != 10 && button6ToggleState == true);
	cutOffType6->setVisible(button6ToggleState == true);
}