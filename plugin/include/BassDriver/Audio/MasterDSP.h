#pragma once

#include "SaturatorDSP.h"
#include "CompressorDSP.h"

// all the ways the two halves can be configured
enum stage_config { bothCompFirst, bothSatFirst, compOnly, satOnly, neither };

#define MAX_BUF_SIZE 2048

class BassDriverCore {
private:
  Saturator sat;
  Compressor comp;

  float dryBuf[MAX_BUF_SIZE];
  // params
  float inputGain;
  float dryGain;
  stage_config config = bothCompFirst;

public:
  BassDriverCore() = default;
  void init(double sampleRate);
  void updateParams(apvts& tree);
  void processChunk(float*, int numSamples);
  Compressor* getCompressor() { return &comp; }

private:
  // helpers
  void applyInputGain(float* buf, int numSamples);
  void copyDryBuffer(float* buf, int numSamples);
  void addDryMix(float* buf, int numSamples);
  //
};
