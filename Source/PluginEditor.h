#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class TunerEngineDemoAudioProcessorEditor : public AudioProcessorEditor {
public:
	TunerEngineDemoAudioProcessorEditor(TunerEngineDemoAudioProcessor &);

	void paint(Graphics &) override;

private:
	TunerEngineDemoAudioProcessor &processor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TunerEngineDemoAudioProcessorEditor)
};
