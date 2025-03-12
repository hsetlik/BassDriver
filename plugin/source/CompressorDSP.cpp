#include "BassDriver/Audio/CompressorDSP.h"
#include <cmath>
#include "BassDriver/Identifiers.h"
#include "juce_audio_basics/juce_audio_basics.h"

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
  return windowLevelN1;
}

//----------------------------------------------------
void EnvelopeFollower::setAttackHz(float norm) {
  static frange_t atkRange(3.0f, 50.0f);
  attackHz = atkRange.convertFrom0to1(1.0f - norm);
}

void EnvelopeFollower::setReleaseHz(float norm) {
  static frange_t rlsRange(1.0f, 40.0f);
  releaseHz = rlsRange.convertFrom0to1(1.0f - norm);
}

void EnvelopeFollower::init(double sampleRate) {
  auto aParams = *atkFilter.getParams();
  aParams.cutoff = 35.0f;
  aParams.order = 4;
  atkFilter.setParams(aParams);
  atkFilter.setFreqSmoothing(true);
  atkFilter.prepare(sampleRate);

  auto rParams = *rlsFilter.getParams();
  rParams.cutoff = 35.0f;
  rParams.order = 4;
  rlsFilter.setParams(rParams);
  rlsFilter.prepare(sampleRate);

  chunkMeter.setWindowSize(500);
}

void EnvelopeFollower::update(float atk, float rls) {
  setAttackHz(atk);
  setReleaseHz(rls);
}

float EnvelopeFollower::process(float input) {
  currentRMSLevel = chunkMeter.process(input);
  float p = pd.process(input);
  // float freq = chunkMeter.isGainIncreasing() ? attackHz : releaseHz;
  // atkFilter.setFrequency(freq);
  float aValue = raFilter.process(p);
  return aValue;
}

//=================================================================================

void Compressor::init(double sampleRate) {
  ef.init(sampleRate);
  ef.update(0.125f, 0.3f);
  inGain = 1.0f;
  threshold = juce::Decibels::decibelsToGain(-20.0f);
  ratio = 1.5f;
  outGain = 1.0f;
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

  ef.update(_attack, _release);
  inGain = juce::Decibels::decibelsToGain(_in);
  threshold = juce::Decibels::decibelsToGain(_thresh);
  ratio = _ratio;
  outGain = juce::Decibels::decibelsToGain(_out);
}

void Compressor::processChunk(float* data, int numSamples) {
  for (int i = 0; i < numSamples; ++i)
    data[i] = processSample(data[i]);
}

static float gainForLevel(float level, float thresh, float ratio) {
  if (level < thresh)
    return 1.0f;
  return thresh + (level - thresh) / ratio;
}

float Compressor::processSample(float input) {
  float s = input * inGain;
  envLevel = ef.process(s);
  currentGain = gainForLevel(envLevel, threshold, ratio);
  return s * currentGain * outGain;
}

float Compressor::currentGainReductionDB() {
  return juce::Decibels::gainToDecibels(currentGain);
}

float Compressor::currentInputLevelNorm() {
  return envLevel;
}

float Compressor::currentInputLevelDB() {
  return juce::Decibels::gainToDecibels(envLevel);
}
