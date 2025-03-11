#include "BassDriver/Common.h"
#include "juce_audio_processors/juce_audio_processors.h"

static double sampleHz = 44100.0;

void SampleRate::set(double rate) {
  sampleHz = rate;
}
double SampleRate::get() {
  return sampleHz;
}

bool readBoolTreeParam(apvts& tree, const juce::String& paramID) {
  auto* param =
      dynamic_cast<juce::AudioParameterBool*>(tree.getParameter(paramID));
  return param->get();
}
