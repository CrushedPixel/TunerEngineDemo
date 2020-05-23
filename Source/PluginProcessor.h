#pragma once

#include <JuceHeader.h>
#include <TunerEngine/pitch/PitchCurveCorrector.h>
#include <TunerEngine/tuner/Tuner.h>
#include "Settings.h"

class TunerEngineDemoAudioProcessor : public AudioProcessor {
public:
	TunerEngineDemoAudioProcessor();

	void prepareToPlay(double sampleRate, int samplesPerBlock) override;

	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations

	bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

#endif

	void processBlock(AudioBuffer<float> &, MidiBuffer &) override;

	AudioProcessorEditor *createEditor() override;

	bool hasEditor() const override;

	const String getName() const override;

	bool acceptsMidi() const override;

	bool producesMidi() const override;

	double getTailLengthSeconds() const override;

	int getNumPrograms() override;

	int getCurrentProgram() override;

	void setCurrentProgram(int index) override;

	const String getProgramName(int index) override;

	void changeProgramName(int index, const String &newName) override;

	void getStateInformation(MemoryBlock &destData) override;

	void setStateInformation(const void *data, int sizeInBytes) override;

private:
	const std::shared_ptr<Settings> settings;

	std::shared_ptr<crispy_audio::PitchCurveCorrector> pitchCurveCorrector;
	std::unique_ptr<crispy_audio::Tuner> tuner;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TunerEngineDemoAudioProcessor)
};
