#pragma once
#include "BassDriver/Audio/RollingAverage.h"
#include "IIRFilter.h"

// stuff for envelope following

/* This peak detector is does not contain any sort of
 * output filtering, it simply returns the largest absolute
 * value between its inputs previous two zero crossings
 * */

#define PEAK_INTERNAL_FILTER

class PeakDetector {
private:
  float prevPhasePeak = 0.0f;
  float currentPeak = 0.0f;
  RollingAverage filter;

public:
  PeakDetector() : filter(65) {}
  float process(float input);
};

// RMS detector
#define RMS_WINDOW_MAX 4096
#define RMS_WINDOW_MIN 50
#define RMS_WINDOW_DEFAULT 256

class RMSMeter {
private:
  float windowLevelN2 = 0.0f;
  float windowLevelN1 = 0.0f;
  float currentSum = 0.0f;
  int windowSize = RMS_WINDOW_DEFAULT;
  int windowPos = 0;
  bool gainIncreasing = false;

public:
  RMSMeter() = default;
  void setWindowSize(int size) { windowSize = size; }
  float process(float input);
  bool isGainIncreasing() const { return gainIncreasing; }
};

// this uses the above
// PeakDetector and RMSMeter
// classes to give us a controllable
// envelope follower
class EnvelopeFollower {
private:
  RMSMeter chunkMeter;
  float currentRMSLevel;
  PeakDetector pd;
  CascadeIIR atkFilter;
  CascadeIIR rlsFilter;
  RollingAverage raFilter;
  float attackHz;
  float releaseHz;
  // helpers for the freq ranges
  // here
  void setAttackHz(float norm);
  void setReleaseHz(float norm);

public:
  EnvelopeFollower() : raFilter(10) {}
  void init(double sampleRate);
  void update(float atk, float rls);
  float process(float input);
  float getRMSLevel() const { return currentRMSLevel; }
};

//=================================================================================

class Compressor {
private:
  EnvelopeFollower ef;
  float envLevel = 0.0f;
  float currentGain;

  // params
  float inGain;
  float threshold;
  float ratio;
  float outGain;

public:
  Compressor() = default;
  void init(double sampleRate);
  void updateParams(apvts& tree);
  void processChunk(float* data, int numSamples);
  float processSample(float input);
  // getters for the compression graph
  float currentInputLevelNorm();
  float currentInputLevelDB();
  float currentGainReductionDB();
};
