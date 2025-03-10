#include "BassDriver/GUI/InputPanel.h"
#include "BassDriver/Identifiers.h"

InputPanel::InputPanel(apvts& state)
    : orderBtn(state, ID::stageOrder.toString()),
      dryLevelSlider(state, ID::dryLevel.toString()),
      preGainSlider(state, ID::preampGain.toString()) {
  dryLevelSlider.getSlider()->setSliderStyle(juce::Slider::Rotary);
  preGainSlider.getSlider()->setSliderStyle(juce::Slider::Rotary);
  addAndMakeVisible(dryLevelSlider);
  addAndMakeVisible(preGainSlider);
  addAndMakeVisible(orderBtn);
}

void InputPanel::resized() {
  auto fBounds = getLocalBounds().toFloat();
  const float dX = std::min(fBounds.getHeight(), fBounds.getWidth() / 4.0f);
  dryLevelSlider.setBounds(fBounds.removeFromLeft(dX).toNearestInt());
  preGainSlider.setBounds(fBounds.removeFromLeft(dX).toNearestInt());
  orderBtn.setBounds(fBounds.removeFromLeft(dX).toNearestInt());
}
