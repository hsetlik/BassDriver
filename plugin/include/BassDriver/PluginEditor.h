#pragma once

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
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BassDriverProcessorEditor)
};

}  // namespace audio_plugin
