#include "BassDriver/GUI/InputPanel.h"
#include "BassDriver/Identifiers.h"

InputPanel::InputPanel(apvts& state)
    : orderBtn(state, ID::stageOrder.toString()),
      dryLevelSlider(state, ID::dryLevel.toString()),
      preGainSlider(state, ID::preampGain.toString()),
      eqBtn(state, ID::EQ_active.toString()),
      showEqButton("Show EQ Bands") {
  dryLevelSlider.getSlider()->setSliderStyle(juce::Slider::Rotary);
  preGainSlider.getSlider()->setSliderStyle(juce::Slider::Rotary);
  addAndMakeVisible(dryLevelSlider);
  addAndMakeVisible(preGainSlider);
  addAndMakeVisible(orderBtn);
  addAndMakeVisible(eqBtn);
  addAndMakeVisible(showEqButton);
}

void InputPanel::resized() {
  auto fBounds = getLocalBounds().toFloat();
  const float dX = std::min(fBounds.getHeight(), fBounds.getWidth() / 6.0f);
  dryLevelSlider.setBounds(fBounds.removeFromLeft(dX).toNearestInt());
  preGainSlider.setBounds(fBounds.removeFromLeft(dX).toNearestInt());
  orderBtn.setBounds(fBounds.removeFromLeft(dX).toNearestInt());
  eqBtn.setBounds(fBounds.removeFromLeft(dX).toNearestInt());
  showEqButton.setBounds(fBounds.toNearestInt());
}
