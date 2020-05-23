#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <TunerEngine/pitch/BasicPitchCurveCorrector.h>
#include <TunerEngine/pitch/LivePitchDetector.h>
#include <TunerEngine/tuner/LiveTuner.h>
#include <TunerEngine/tuner/OfflineTuner.h>

#define LIVE_TUNING 0

TunerEngineDemoAudioProcessor::TunerEngineDemoAudioProcessor() :
		AudioProcessor(BusesProperties()
				               .withInput("Input", AudioChannelSet::stereo(), true)
				               .withOutput("Output", AudioChannelSet::stereo(), true)),
		settings(new Settings()) {}

void TunerEngineDemoAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
	// the sample rate changed -
	// initialize the pitch curve corrector and tuner
	pitchCurveCorrector = std::make_shared<crispy_audio::BasicPitchCurveCorrector>(settings, sampleRate);

#if LIVE_TUNING
	auto pitchDetector = std::make_unique<crispy_audio::LivePitchDetector>(settings, sampleRate);
	tuner = crispy_audio::LiveTuner::make_unique(
			settings, sampleRate,
			std::move(pitchDetector), pitchCurveCorrector,
			24 /* C1 */, -12);
#else
	auto pitchDetector = std::make_unique<crispy_audio::OfflinePitchDetector>(settings, sampleRate);
	tuner = crispy_audio::OfflineTuner::make_unique(
			settings, sampleRate,
			std::move(pitchDetector), pitchCurveCorrector,
			24 /* C1 */, -12);
#endif

	// report the latency to the host
	setLatencySamples(tuner->getLatency());
}

void TunerEngineDemoAudioProcessor::releaseResources() {
}

void TunerEngineDemoAudioProcessor::processBlock(AudioBuffer<float> &buffer, MidiBuffer &midiMessages) {
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	assert(totalNumInputChannels > 0);

	// the TunerEngine only supports single-channel input,
	// so we simply tune the first input channel's data
	// and send it to all output channels
	for (int i = 0; i < buffer.getNumSamples(); i++) {
		auto sample = buffer.getSample(0, i);
		auto tuned /* hehe */ = tuner->process(sample);

		for (int channel = 0; channel < totalNumOutputChannels; channel++) {
			*buffer.getWritePointer(channel, i) = tuned;
		}
	}
}

/*
 * ========================================================================
 * EVERYTHING BELOW IS JUST BOILERPLATE CODE UNRELATED TO THE TunerEngine
 * ========================================================================
 */

const String TunerEngineDemoAudioProcessor::getName() const {
	return JucePlugin_Name;
}

bool TunerEngineDemoAudioProcessor::acceptsMidi() const {
	return false;
}

bool TunerEngineDemoAudioProcessor::producesMidi() const {
	return false;
}

double TunerEngineDemoAudioProcessor::getTailLengthSeconds() const {
	return 0.0;
}

int TunerEngineDemoAudioProcessor::getNumPrograms() {
	return 1;
}

int TunerEngineDemoAudioProcessor::getCurrentProgram() {
	return 0;
}

void TunerEngineDemoAudioProcessor::setCurrentProgram(int index) {
}

const String TunerEngineDemoAudioProcessor::getProgramName(int index) {
	return {};
}

void TunerEngineDemoAudioProcessor::changeProgramName(int index, const String &newName) {
}

bool TunerEngineDemoAudioProcessor::hasEditor() const {
	return true;
}

AudioProcessorEditor *TunerEngineDemoAudioProcessor::createEditor() {
	return new TunerEngineDemoAudioProcessorEditor(*this);
}

void TunerEngineDemoAudioProcessor::getStateInformation(MemoryBlock &destData) {
}

void TunerEngineDemoAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
}

bool TunerEngineDemoAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const {
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
	    && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo()) {
		return false;
	}

	// This checks if the input layout matches the output layout
	return layouts.getMainOutputChannelSet() == layouts.getMainInputChannelSet();
}

AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
	return new TunerEngineDemoAudioProcessor();
}
