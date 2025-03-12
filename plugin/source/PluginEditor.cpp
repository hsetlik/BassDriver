#include "BassDriver/PluginEditor.h"
#include "BassDriver/PluginProcessor.h"

namespace audio_plugin {
BassDriverProcessorEditor::BassDriverProcessorEditor(
    BassDriverAudioProcessor& p)
    : AudioProcessorEditor(&p),
      processorRef(p),
      inPanel(p.tree),
      dPanel(p.tree),
      cPanel(p.tree, p.core.getCompressor()) {
  juce::ignoreUnused(processorRef);
  setLookAndFeel(&lookAndFeel);
  addAndMakeVisible(&inPanel);
  addAndMakeVisible(&dPanel);
  addAndMakeVisible(&cPanel);
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(1000, 620);
}

BassDriverProcessorEditor::~BassDriverProcessorEditor() {
  setLookAndFeel(nullptr);
}

void BassDriverProcessorEditor::paint(juce::Graphics& g) {
  // (Our component is opaque, so we must completely fill the background with a
  // solid colour)
  g.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void BassDriverProcessorEditor::resized() {
  auto fBounds = getLocalBounds().toFloat();
  constexpr float inPanelHeight = 120.0f;
  auto iBounds = fBounds.removeFromTop(inPanelHeight);
  inPanel.setBounds(iBounds.toNearestInt());
  auto dBounds = fBounds.removeFromLeft(fBounds.getWidth() * 0.5f);
  // cbounds = 500 x 500
  // each slider/graph will be 167 X 167
  dPanel.setBounds(dBounds.toNearestInt());
  cPanel.setBounds(fBounds.toNearestInt());
}
}  // namespace audio_plugin
