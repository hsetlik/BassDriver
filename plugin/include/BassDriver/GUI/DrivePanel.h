#pragma once
#include "ParamSlider.h"
#include "juce_core/system/juce_PlatformDefs.h"

class DrivePanel : public juce::Component, juce::Button::Listener {
private:
  ParamToggle bypToggle;
  juce::Label sectionLabel;
  LabeledParamSlider inGainSlider;
  LabeledParamSlider clipAmtSlider;
  LabeledParamSlider filterSlider;
  LabeledParamSlider outGainSlider;

public:
  DrivePanel(apvts& tree);
  void resized() override;
  void buttonClicked(juce::Button* b) override;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DrivePanel)
};
