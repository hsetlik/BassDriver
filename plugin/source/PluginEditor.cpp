#include "BassDriver/PluginEditor.h"
#include "BassDriver/PluginProcessor.h"

namespace audio_plugin {
BassDriverProcessorEditor::BassDriverProcessorEditor(
    BassDriverAudioProcessor& p)
    : AudioProcessorEditor(&p),
      processorRef(p),
      inPanel(p.tree),
      dPanel(p.tree),
      cPanel(p.tree) {
  juce::ignoreUnused(processorRef);
  addAndMakeVisible(&inPanel);
  addAndMakeVisible(&dPanel);
  addAndMakeVisible(&cPanel);
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(800, 600);
}

BassDriverProcessorEditor::~BassDriverProcessorEditor() {}

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
  dPanel.setBounds(dBounds.toNearestInt());
  cPanel.setBounds(fBounds.toNearestInt());
}
}  // namespace audio_plugin
