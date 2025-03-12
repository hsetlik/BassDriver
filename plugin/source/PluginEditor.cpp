#include "BassDriver/PluginEditor.h"
#include "BassDriver/PluginProcessor.h"

namespace audio_plugin {
BassDriverProcessorEditor::BassDriverProcessorEditor(
    BassDriverAudioProcessor& p)
    : AudioProcessorEditor(&p),
      processorRef(p),
      inPanel(p.tree),
      dPanel(p.tree),
      cPanel(p.tree, p.core.getCompressor()),
      ePanel(p.tree) {
  juce::ignoreUnused(processorRef);
  setLookAndFeel(&lookAndFeel);
  addAndMakeVisible(&inPanel);
  inPanel.showEqButton.addListener(this);
  addAndMakeVisible(&dPanel);
  addAndMakeVisible(&cPanel);
  addAndMakeVisible(&ePanel);
  ePanel.setVisible(false);
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

void BassDriverProcessorEditor::buttonClicked(juce::Button* b) {
  eqViewOpen = b->getToggleState();
  resized();
}

void BassDriverProcessorEditor::resized() {
  auto fBounds = getLocalBounds().toFloat();
  constexpr float inPanelHeight = 120.0f;
  auto iBounds = fBounds.removeFromTop(inPanelHeight);
  inPanel.setBounds(iBounds.toNearestInt());
  auto dBounds = fBounds.removeFromLeft(fBounds.getWidth() * 0.4f);
  // cbounds = 600 x 500
  dPanel.setBounds(dBounds.toNearestInt());

  cPanel.setBounds(fBounds.toNearestInt());
  // switch the EQ view on and off
  if (eqViewOpen) {
    // turn off the cPanel
    cPanel.setEnabled(false);
    auto eBounds = fBounds.removeFromTop(fBounds.getHeight() * 0.75f);
    ePanel.setVisible(true);
    ePanel.setEnabled(true);
    ePanel.setBounds(eBounds.toNearestInt());
    ePanel.toFront(false);
  } else {
    ePanel.setVisible(false);
    ePanel.setEnabled(false);
    cPanel.setEnabled(true);
    cPanel.toFront(false);
  }
}
}  // namespace audio_plugin
