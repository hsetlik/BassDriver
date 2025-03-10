#pragma once

#include "ParamSlider.h"

class CompressorPanel : public juce::Component {
private:
  ParamToggle activeBtn;
  LabeledParamSlider inGainSlider;
  LabeledParamSlider threshSlider;
  LabeledParamSlider ratioSlider;
  LabeledParamSlider attackSlider;
  LabeledParamSlider releaseSlider;
  LabeledParamSlider outGainSlider;

  LabeledParamSlider* sliders[6] = {&inGainSlider,  &threshSlider,
                                    &ratioSlider,   &attackSlider,
                                    &releaseSlider, &outGainSlider};

public:
  CompressorPanel(apvts& state);
  void resized() override;
};
