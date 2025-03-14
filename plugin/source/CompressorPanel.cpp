#include "BassDriver/GUI/CompressorPanel.h"
#include "BassDriver/Identifiers.h"

CompressorPanel::CompressorPanel(apvts& state, Compressor* c)
    : graph(c),
      activeBtn(state, ID::COMP_active.toString()),
      inGainSlider(state, ID::COMP_inGain.toString()),
      threshSlider(state, ID::COMP_thresh.toString()),
      ratioSlider(state, ID::COMP_ratio.toString()),
      kneeSlider(state, ID::COMP_knee.toString()),
      attackSlider(state, ID::COMP_attack.toString()),
      releaseSlider(state, ID::COMP_release.toString()),
      outGainSlider(state, ID::COMP_outGain.toString()) {
  addAndMakeVisible(graph);
  addAndMakeVisible(activeBtn);
  activeBtn.addListener(this);
  sectionLabel.setText("Compressor", juce::dontSendNotification);
  addAndMakeVisible(sectionLabel);
  for (int i = 0; i < 7; ++i) {
    addAndMakeVisible(sliders[i]);
  }
}

void CompressorPanel::buttonClicked(juce::Button* b) {
  bool en = b->getToggleState();
  for (int i = 0; i < 7; i++) {
    sliders[i]->setEnabled(en);
  }
}

void CompressorPanel::resized() {
  // the panel is 600px wide and 500px tall in total
  auto bBounds = getLocalBounds().toFloat();
  auto lBounds = bBounds.removeFromTop(20.0f);
  sectionLabel.setBounds(lBounds.removeFromLeft(65.0f).toNearestInt());
  activeBtn.setBounds(lBounds.toNearestInt());
  // remaining area: 600 x 480
  // dY = height / 4 = 120
  // dX = width / 4 = 150
  const int dY = 120;
  const int dX = 150;
  const int y0 = lBounds.toNearestInt().getBottom();
  // left column
  inGainSlider.setBounds(0, y0, dX, dY);
  threshSlider.setBounds(0, y0 + dY, dX, dY);
  ratioSlider.setBounds(0, y0 + dY * 2, dX, dY);
  kneeSlider.setBounds(0, y0 + dY * 3, dX, dY);
  // bottom row
  attackSlider.setBounds(dX, y0 + dY * 3, dX, dY);
  releaseSlider.setBounds(dX * 2, y0 + dY * 3, dX, dY);
  outGainSlider.setBounds(dX * 3, y0 + dY * 3, dX, dY);
  // graph
  // graph dimensions are 400 x 360
  graph.setBounds(dX, y0, 2 * dX, 3 * dY);
}
