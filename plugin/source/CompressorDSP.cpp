#include "BassDriver/Audio/CompressorDSP.h"
#include <cmath>

float PeakDetector::process(float input) {
  static float prevInput = 0.0f;
  // zero crossing
  if (std::signbit(prevInput) != std::signbit(input)) {
    prevPhasePeak = currentPeak;
    currentPeak = 0.0f;
  }
  prevInput = input;
  float mag = std::fabs(input);
  if (mag > currentPeak)
    currentPeak = mag;
  return prevPhasePeak;
}

float RMSMeter::process(float input) {
  if (windowPos == windowSize) {
    float meanSquare = currentSum / (float)windowSize;
    windowLevelN1 = std::sqrtf(meanSquare);
    windowPos = 0;
    currentSum = 0.0f;
  } else {
    ++windowPos;
  }
  currentSum += (input * input);
  return windowLevelN1;
}
