/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../Assets/PlotComponent.h"

//==============================================================================
/**
*/
extern ScopedPointer<PlotComponent> thePlotComponent;
class FilterTestAudioProcessorEditor  : public AudioProcessorEditor,
										public ChangeListener,
										public Timer
{
public:
    FilterTestAudioProcessorEditor (FilterTestAudioProcessor&);
    ~FilterTestAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	float scopeData[1024];

	void changeListenerCallback(ChangeBroadcaster* sender) override;
	void timerCallback() override;

	class BandEditor : public Component
		              
	{
	public:
		BandEditor(const int i, FilterTestAudioProcessor& processor);

		void resized() override;
		void updateControls(int type);
		void setFrequency(float frequency);
		Path bandFrequencyResponse;

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BandEditor)

		int index;
		FilterTestAudioProcessor& processor;

		GroupComponent	frame;
		ComboBox		filterType;
		Slider			frequency;
		Slider			resonance;
		Slider			gain;
		OwnedArray<AudioProcessorValueTreeState::SliderAttachment>attachments;

	};

	//void updateVisibility();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FilterTestAudioProcessor& processor;
	ScopedPointer<Slider> frequencySlider;
	ScopedPointer<Label> frequencyLabel;

	ScopedPointer<Slider> resonanceSlider;
	ScopedPointer<Label> resonanceLabel;

	ScopedPointer<Slider> gainSlider;
	ScopedPointer<Label> gainLabel;

	ScopedPointer<ComboBox> filterType;
	ScopedPointer<ComboBox> oversampling;
	ScopedPointer<Label> cutOffType;

	// filter 2
	ScopedPointer<Slider> frequency2Slider;
	ScopedPointer<Label> frequency2Label;

	ScopedPointer<Slider> resonance2Slider;
	ScopedPointer<Label> resonance2Label;

	ScopedPointer<Slider> gain2Slider;
	ScopedPointer<Label> gain2Label;

	ScopedPointer<ComboBox> filter2Type;
	ScopedPointer<ComboBox> oversampling2;
	ScopedPointer<Label> cutOffType2;

	// filter 3
	ScopedPointer<Slider> frequency3Slider;
	ScopedPointer<Label> frequency3Label;

	ScopedPointer<Slider> resonance3Slider;
	ScopedPointer<Label> resonance3Label;

	ScopedPointer<Slider> gain3Slider;
	ScopedPointer<Label> gain3Label;

	ScopedPointer<ComboBox> filter3Type;
	ScopedPointer<ComboBox> oversampling3;
	ScopedPointer<Label> cutOffType3;

	// filter 4
	ScopedPointer<Slider> frequency4Slider;
	ScopedPointer<Label> frequency4Label;

	ScopedPointer<Slider> resonance4Slider;
	ScopedPointer<Label> resonance4Label;

	ScopedPointer<Slider> gain4Slider;
	ScopedPointer<Label> gain4Label;

	ScopedPointer<ComboBox> filter4Type;
	ScopedPointer<ComboBox> oversampling4;
	ScopedPointer<Label> cutOffType4;

	// filter 5
	ScopedPointer<Slider> frequency5Slider;
	ScopedPointer<Label> frequency5Label;

	ScopedPointer<Slider> resonance5Slider;
	ScopedPointer<Label> resonance5Label;

	ScopedPointer<Slider> gain5Slider;
	ScopedPointer<Label> gain5Label;

	ScopedPointer<ComboBox> filter5Type;
	ScopedPointer<ComboBox> oversampling5;
	ScopedPointer<Label> cutOffType5;

	// filter 6
	ScopedPointer<Slider> frequency6Slider;
	ScopedPointer<Label> frequency6Label;

	ScopedPointer<Slider> resonance6Slider;
	ScopedPointer<Label> resonance6Label;

	ScopedPointer<Slider> gain6Slider;
	ScopedPointer<Label> gain6Label;

	ScopedPointer<ComboBox> filter6Type;
	ScopedPointer<ComboBox> oversampling6;
	ScopedPointer<Label> cutOffType6;

	ScopedPointer<TextButton> filter1Button;
	ScopedPointer<TextButton> filter2Button;
	ScopedPointer<TextButton> filter3Button;
	ScopedPointer<TextButton> filter4Button;
	ScopedPointer<TextButton> filter5Button;
	ScopedPointer<TextButton> filter6Button;

#ifdef JUCE_OPENGL
	OpenGLContext openGLContext;
#endif
	
	OwnedArray<BandEditor>		  bandEditors;

	juce::Rectangle<int>          plotFrame;

	Path                    analyserPath;
	Path					analyserPathOutput;
	Path					frequencyResponse;

	void updateFrequencyResponses();

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> frequencyAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resonanceAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> oversamplingAttachment;
	//ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> addFilterAttachment;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> frequency2Attachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resonance2Attachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gain2Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterType2Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> oversampling2Attachment;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> frequency3Attachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resonance3Attachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gain3Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterType3Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> oversampling3Attachment;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> frequency4Attachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resonance4Attachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gain4Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterType4Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> oversampling4Attachment;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> frequency5Attachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resonance5Attachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gain5Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterType5Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> oversampling5Attachment;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> frequency6Attachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resonance6Attachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gain6Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterType6Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> oversampling6Attachment;

	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> button1Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> button2Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> button3Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> button4Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> button5Attachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> button6Attachment;

	inline float indexToX (float index, float minFreq) const;
	inline float binToY(float bin, const juce::Rectangle<float> bounds) const;

	void updateVisibility();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterTestAudioProcessorEditor)
};
