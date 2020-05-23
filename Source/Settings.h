#pragma once

#include <JuceHeader.h>
#include <TunerEngine/tuner/OfflineTuner.h>
#include <TunerEngine/pitch/BasicPitchCurveCorrector.h>
#include <TunerEngine/pitch/OfflinePitchDetector.h>

/**
 * Demonstrates how to pass settings to the TunerEngine.
 * The values returned by the functions are allowed change anytime!
 */
class Settings : public crispy_audio::OfflineTuner::Settings,
                 public crispy_audio::BasicPitchCurveCorrector::Settings,
                 public crispy_audio::OfflinePitchDetector::Settings {

public:
	crispy_audio::note_t getFormantShift() const override {
		return 0;
	}

	float getFormantCorrection() const override {
		// formant correction 1 means natural sound,
		// formant correction 0 means more noticeable glitches,
		// emphasizing the T-Pain effect
		return 1;
	}

	crispy_audio::midi_note_t getMinTargetNote() const override {
		return 0; // C-1
	}

	crispy_audio::midi_note_t getMaxTargetNote() const override {
		return 107; // B7
	}

	NoteLegality getNoteLegality(crispy_audio::midi_note_t midiNote) const override {
		/*
		 * C Major scale
		 */
		switch (midiNote % 12) {
			case 0:  // C
			case 2:  // D
			case 4:  // E
			case 5:  // F
			case 7:  // G
			case 9:  // A
			case 11: // B
				return ENABLED;
			default:
				return DISABLED;
		}
	}

	crispy_audio::note_t getPitchTolerance() const override {
		return 0;
	}

	crispy_audio::seconds_t getTimeTolerance() const override {
		return 0;
	}

	crispy_audio::note_t getPitchShift() const override {
		return 0;
	}

	crispy_audio::frequency_t getA4Frequency() const override {
		return 440;
	}

	crispy_audio::seconds_t getTransitionTime() const override {
		// 0 for the strongest effect possible.
		// values around 0.03s give more natural results.
		return 0;
	}

	crispy_audio::seconds_t getRetuneSpeed() const override {
		// 0 for the strongest effect possible.
		// values around 0.05s give more natural results.
		return 0;
	}

	float getCorrectionAmount() const override {
		return 1;
	}

	float getPitchDetectionThreshold() const override {
		// a value that has yielded good results with most inputs.
		// for bad microphones, a higher value may be suitable.
		return 0.17;
	}

	float getEnergyThreshold() const override {
		// you probably shouldn't touch this.
		return 0.0000001;
	}

	crispy_audio::note_t getMinInputNote() const override {
		return 24; // C1
	}

	crispy_audio::note_t getMaxInputNote() const override {
		return 95; // B6
	}

	float getVoicementThreshold() override {
		// a value that has yielded good results with most inputs.
		return 0.6;
	}

};