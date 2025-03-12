#pragma once

#include "ParamSlider.h"
#include "juce_core/system/juce_PlatformDefs.h"

class InputPanel : public juce::Component {
private:
  ParamToggle orderBtn;
  LabeledParamSlider dryLevelSlider;
  LabeledParamSlider preGainSlider;
  ParamToggle eqBtn;

public:
  juce::ToggleButton showEqButton;
  InputPanel(apvts& state);
  void resized() override;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InputPanel)
};
