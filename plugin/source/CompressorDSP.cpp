#include "BassDriver/Audio/CompressorDSP.h"
#include <cmath>
#include "BassDriver/Identifiers.h"
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_core/juce_core.h"

// idk if this is actually useful but i'm gonna try it
static float floatAbs(float input) {
  static const uint32_t mask = 0x7FFFFFFF;
  uint32_t bits = mask & *reinterpret_cast<uint32_t*>(&input);
  return *reinterpret_cast<float*>(&bits);
}

float PeakDetector::process(float input) {
  static float prevInput = 0.0f;
  // zero crossing
  if (std::signbit(prevInput) != std::signbit(input)) {
    prevPhasePeak = currentPeak;
    currentPeak = 0.0f;
  }
  prevInput = input;
  float mag = floatAbs(input);
  if (mag > currentPeak)
    currentPeak = mag;
#ifdef PEAK_INTERNAL_FILTER
  return filter.process(prevPhasePeak);
#else
  return prevPhasePeak;
#endif
}

float RMSMeter::process(float input) {
  if (windowPos == windowSize) {
    float meanSquare = currentSum / (float)windowSize;
    windowLevelN2 = windowLevelN1;
    windowLevelN1 = std::sqrtf(meanSquare);
    gainIncreasing = windowLevelN1 > windowLevelN2;
    windowPos = 0;
    currentSum = 0.0f;
  } else {
    ++windowPos;
  }
  currentSum += (input * input);
  static float prevOutput = 0.0f;
  if (!fequal(prevOutput, windowLevelN1)) {
    prevOutput = flerp(windowLevelN1, prevOutput, 0.75f);
  }
  return prevOutput;
}

//----------------------------------------------------
static float coeffForTime(float secs, double sampleRate) {
  static const double e = juce::MathConstants<double>::euler;
  const double pwr = (-1.0 / sampleRate) / (double)secs;
  return (float)std::pow(e, pwr);
}

void EnvelopeFollower::setAttackNorm(float norm) {
  static frange_t atkRange = rangeWithCenter(3.0f, 1800.0f, 35.0f);
  auto newVal = atkRange.convertFrom0to1(norm) / 1000.0f;
  if (!fequal(newVal, attackSecs)) {
    attackSecs = newVal;
    attackExp = coeffForTime(attackSecs, SampleRate::get());
  }
}

void EnvelopeFollower::setReleaseNorm(float norm) {
  static frange_t rlsRange = rangeWithCenter(5.0f, 3600.0f, 450.0f);
  auto newVal = rlsRange.convertFrom0to1(norm) / 1000.0f;
  if (!fequal(newVal, releaseSecs)) {
    releaseSecs = newVal;
    releaseExp = coeffForTime(releaseSecs, SampleRate::get());
  }
}

void EnvelopeFollower::init(double sampleRate) {
  juce::ignoreUnused(sampleRate);
  rms.setWindowSize(300);
  setAttackNorm(0.5f);
  setReleaseNorm(0.5f);
}

float EnvelopeFollower::process(float input) {
  currentRMSLevel = rms.process(input);
  float s = pd.process(input);
  if (s > lastOutput) {
    lastOutput = flerp(s, lastOutput, attackExp);
  } else {
    lastOutput = flerp(s, lastOutput, releaseExp);
  }
  return lastOutput;
}

//=================================================================================

void Compressor::init(double sampleRate) {
  ef.init(sampleRate);
  ef.update(0.125f, 0.3f);
  inGainLin = 1.0f;
  thresholdDb = -20.0f;
  ratio = 1.5f;
  outGainLin = 1.0f;
}

void Compressor::updateParams(apvts& tree) {
  const float _in =
      tree.getRawParameterValue(ID::COMP_inGain.toString())->load();
  const float _attack =
      tree.getRawParameterValue(ID::COMP_attack.toString())->load();
  const float _release =
      tree.getRawParameterValue(ID::COMP_release.toString())->load();
  const float _ratio =
      tree.getRawParameterValue(ID::COMP_ratio.toString())->load();
  const float _thresh =
      tree.getRawParameterValue(ID::COMP_thresh.toString())->load();
  const float _out =
      tree.getRawParameterValue(ID::COMP_outGain.toString())->load();
  const float _knee =
      tree.getRawParameterValue(ID::COMP_knee.toString())->load();

  ef.update(_attack, _release);
  inGainLin = juce::Decibels::decibelsToGain(_in);
  thresholdDb = _thresh;
  kneeWidthDb = _knee;
  ratio = _ratio;
  outGainLin = juce::Decibels::decibelsToGain(_out);
}

void Compressor::processChunk(float* data, int numSamples) {
  for (int i = 0; i < numSamples; ++i)
    data[i] = processSample(data[i]);
}

static float gainForLevel(float level, float thresh, float ratio) {
  if (level < thresh)
    return 0.0f;
  return 0.0f - ((level - thresh) * ratio);
}

static float gainForLevel_knee(float level,
                               float thresh,
                               float knee,
                               float ratio) {
  if (level < thresh)
    return 0.0f;
  else if (level < (thresh + knee)) {
    const float r = ((level - thresh) / knee) * ratio;
    return 0.0f - ((level - thresh) * r);
  }
  return 0.0f - ((level - thresh) * ratio);
}

float Compressor::processSample(float input) {
  float s = input * inGainLin;
  envLevel = juce::Decibels::gainToDecibels(ef.process(s));
  float newDb = gainForLevel_knee(envLevel, thresholdDb, kneeWidthDb, ratio);
  if (!fequal(newDb, currentDb)) {
    currentDb = newDb;
    currentGainLin = juce::Decibels::decibelsToGain(currentDb);
  }
  return s * currentGainLin * outGainLin;
}

float Compressor::currentGainDB() const {
  return juce::Decibels::gainToDecibels(currentGainLin);
}

float Compressor::currentInputLevelNorm() const {
  return envLevel;
}

float Compressor::currentInputLevelDB() const {
  float rmsNorm = ef.getRMSLevel() / 0.7071f;
  return juce::Decibels::gainToDecibels(rmsNorm);
}

float Compressor::currentGainNorm() const {
  return currentGainLin;
}
