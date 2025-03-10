#include "BassDriver/GUI/DrivePanel.h"
#include "BassDriver/Identifiers.h"
#include "juce_events/juce_events.h"

DrivePanel::DrivePanel(apvts& state)
    : bypToggle(state, ID::SAT_active.toString()),
      inGainSlider(state, ID::SAT_inGain.toString()),
      clipAmtSlider(state, ID::SAT_clipAmt.toString()),
      filterSlider(state, ID::SAT_outFilter.toString()),
      outGainSlider(state, ID::SAT_outGain.toString()) {
  // set up section label
  sectionLabel.setText("Overdrive", juce::dontSendNotification);
  addAndMakeVisible(sectionLabel);
  addAndMakeVisible(bypToggle);
  addAndMakeVisible(inGainSlider);
  addAndMakeVisible(clipAmtSlider);
  addAndMakeVisible(filterSlider);
  addAndMakeVisible(outGainSlider);
  bypToggle.addListener(this);
}

void DrivePanel::buttonClicked(juce::Button* b) {
  bool enabled = b->getToggleState();
  inGainSlider.setEnabled(enabled);
  clipAmtSlider.setEnabled(enabled);
  filterSlider.setEnabled(enabled);
  outGainSlider.setEnabled(enabled);
}

void DrivePanel::resized() {
  auto fBounds = getLocalBounds().toFloat();
  auto topBounds = fBounds.removeFromTop(18.0f);
  // auto lWidth = sectionLabel.getFont().getStringWidthFloat("Overdrive")
  // + 6.0f;
  auto lBounds = topBounds.removeFromLeft(65.0f);
  sectionLabel.setBounds(lBounds.toNearestInt());
  bypToggle.setBounds(topBounds.toNearestInt());

  auto tBounds = fBounds.removeFromTop(fBounds.getHeight() / 2.0f);
  const float dX = tBounds.getWidth() / 2.0f;
  inGainSlider.setBounds(tBounds.removeFromLeft(dX).toNearestInt());
  clipAmtSlider.setBounds(tBounds.toNearestInt());
  filterSlider.setBounds(fBounds.removeFromLeft(dX).toNearestInt());
  outGainSlider.setBounds(fBounds.toNearestInt());
}
