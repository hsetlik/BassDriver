#pragma once

#include "BassDriver/GUI/CompressorPanel.h"
#include "BassDriver/GUI/CustomLookAndFeel.h"
#include "BassDriver/GUI/DrivePanel.h"
#include "BassDriver/GUI/InputPanel.h"
#include "PluginProcessor.h"

namespace audio_plugin {

class BassDriverProcessorEditor : public juce::AudioProcessorEditor {
public:
  explicit BassDriverProcessorEditor(BassDriverAudioProcessor&);
  ~BassDriverProcessorEditor() override;
  void paint(juce::Graphics&) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  BassDriverAudioProcessor& processorRef;

  InputPanel inPanel;
  DrivePanel dPanel;
  CompressorPanel cPanel;
  BassDriverLnF lookAndFeel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BassDriverProcessorEditor)
};

}  // namespace audio_plugin
