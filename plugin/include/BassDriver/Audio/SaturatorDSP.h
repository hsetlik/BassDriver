#pragma once

#include "../Common.h"
#include "IIRFilter.h"

class Saturator {
private:
  // output filter stuff
  CascadeIIR filter;
  // parameters from the gui
  float inputGain;
  float clipAmt;
  float filterCutoff;
  float outputGain;

public:
  Saturator() = default;
  void init(double sampleRate);
  void processChunk(float* data, int numSamples);
  void updateParams(apvts& tree);

private:
  float processSample(float input);
};
