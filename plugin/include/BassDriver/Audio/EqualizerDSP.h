#pragma once

#include "IIRFilter.h"
#include "juce_core/juce_core.h"

class SevenBandEQ {
private:
  std::array<SingleIIR, 7> filters;
  float outputGain = 1.0f;

public:
  SevenBandEQ() = default;
  void init(double sampleRate);
  void processChunk(float* data, int numSamples);
  void updateParams(apvts& tree);

private:
  float process(float input);
};
