#pragma once

#include "ParamSlider.h"
#include "juce_graphics/juce_graphics.h"

class EqualizerPanel : public juce::Component {
private:
  juce::OwnedArray<LabeledParamSlider> sliders;

public:
  EqualizerPanel(apvts& tree);
  void resized() override;
  void paint(juce::Graphics& g) override;
};
