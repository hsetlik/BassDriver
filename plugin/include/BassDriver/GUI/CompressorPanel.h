#pragma once

#include "BassDriver/GUI/CompressorGraph.h"
#include "ParamSlider.h"

class CompressorPanel : public juce::Component, juce::Button::Listener {
private:
  juce::Label sectionLabel;
  CompressorGraph graph;
  ParamToggle activeBtn;
  LabeledParamSlider inGainSlider;
  LabeledParamSlider threshSlider;
  LabeledParamSlider ratioSlider;
  LabeledParamSlider kneeSlider;
  LabeledParamSlider attackSlider;
  LabeledParamSlider releaseSlider;
  LabeledParamSlider outGainSlider;

  LabeledParamSlider* sliders[7] = {
      &inGainSlider, &threshSlider,  &ratioSlider,  &kneeSlider,
      &attackSlider, &releaseSlider, &outGainSlider};

public:
  CompressorPanel(apvts& state, Compressor* comp);
  void resized() override;
  void buttonClicked(juce::Button* b) override;
};
