#include "PluginProcessor.h"
#include "PluginEditor.h"

TunerEngineDemoAudioProcessorEditor::TunerEngineDemoAudioProcessorEditor(TunerEngineDemoAudioProcessor &p) :
		AudioProcessorEditor(&p), processor(p) {
	setSize(400, 300);
}

void TunerEngineDemoAudioProcessorEditor::paint(Graphics &g) {
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	g.setColour(Colours::white);
	g.setFont(15.0f);
	g.drawFittedText("Hello World!", getLocalBounds(), Justification::centred, 1);
}
