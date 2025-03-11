#include "BassDriver/GUI/CompressorPanel.h"
#include "BassDriver/Identifiers.h"

CompressorPanel::CompressorPanel(apvts& state, Compressor* c)
    : graph(c),
      activeBtn(state, ID::COMP_active.toString()),
      inGainSlider(state, ID::COMP_inGain.toString()),
      threshSlider(state, ID::COMP_thresh.toString()),
      ratioSlider(state, ID::COMP_ratio.toString()),
      attackSlider(state, ID::COMP_attack.toString()),
      releaseSlider(state, ID::COMP_release.toString()),
      outGainSlider(state, ID::COMP_outGain.toString()) {
  addAndMakeVisible(graph);
  addAndMakeVisible(activeBtn);
  activeBtn.addListener(this);
  sectionLabel.setText("Compressor", juce::dontSendNotification);
  addAndMakeVisible(sectionLabel);
  for (int i = 0; i < 6; ++i) {
    addAndMakeVisible(sliders[i]);
  }
}

void CompressorPanel::buttonClicked(juce::Button* b) {
  bool en = b->getToggleState();
  for (int i = 0; i < 6; i++) {
    sliders[i]->setEnabled(en);
  }
}

void CompressorPanel::resized() {
  auto bBounds = getLocalBounds().toFloat();
  auto lBounds = bBounds.removeFromTop(18.0f);
  sectionLabel.setBounds(lBounds.removeFromLeft(65.0f).toNearestInt());
  activeBtn.setBounds(lBounds.toNearestInt());
  float dX = bBounds.getWidth() / 3.0f;
  const float dY = bBounds.getHeight() / 3.0f;
  auto lColumn = bBounds.removeFromLeft(dX);
  inGainSlider.setBounds(lColumn.removeFromTop(dY).toNearestInt());
  threshSlider.setBounds(lColumn.removeFromTop(dY).toNearestInt());
  ratioSlider.setBounds(lColumn.toNearestInt());
  auto bRow = bBounds.removeFromBottom(dY);
  dX = bRow.getWidth() / 3.0f;
  attackSlider.setBounds(bRow.removeFromLeft(dX).toNearestInt());
  releaseSlider.setBounds(bRow.removeFromLeft(dX).toNearestInt());
  outGainSlider.setBounds(bRow.toNearestInt());
  graph.setBounds(bBounds.toNearestInt());
}
