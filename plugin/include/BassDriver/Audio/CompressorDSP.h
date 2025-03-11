#pragma once
#include "IIRFilter.h"

// stuff for envelope following

/* This peak detector is does not contain any sort of
 * output filtering, it simply returns the largest absolute
 * value between its inputs previous two zero crossings
 * */
class PeakDetector {
private:
  float prevPhasePeak = 0.0f;
  float currentPeak = 0.0f;

public:
  PeakDetector() = default;
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

public:
  RMSMeter() = default;
  void setWindowSize(int size) { windowSize = size; }
  float process(float input);
  bool isGainIncreasing();
};

// this uses the above
// PeakDetector and RMSMeter
// classes to give us a controllable
// envelope follower
class EnvelopeFollower {
private:
  RMSMeter chunkMeter;
};
