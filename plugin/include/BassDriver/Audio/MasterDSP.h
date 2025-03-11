#pragma once

#include "SaturatorDSP.h"
#include "CompressorDSP.h"

// all the ways the two halves can be configured
enum stage_config { bothCompFirst, bothSatFirst, compOnly, satOnly, neither };

class BassDriverCore {
private:
  Saturator sat;
  Compressor comp;

  // params
  float inputGain;
  stage_config config = bothCompFirst;

public:
  BassDriverCore() = default;
  void init(double sampleRate);
  void updateParams(apvts& tree);
  void processChunk(float*, int numSamples);

private:
  // helpers
  void applyInputGain(float* buf, int numSamples);
};
