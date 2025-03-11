#include "BassDriver/Audio/SaturatorDSP.h"
#include "BassDriver/Audio/IIRFilter.h"
#include "BassDriver/Identifiers.h"
#include "juce_audio_basics/juce_audio_basics.h"

void Saturator::init(double sampleRate) {
  // 1. set up the input filter
  auto fParams = *filter.getParams();
  fParams.filterType = iir_cascade_t::ButterworthLowPass1;
  fParams.cutoff = 400.0f;
  filter.setParams(fParams);
  filter.prepare(sampleRate);

  inputGain = juce::Decibels::decibelsToGain(15.0f);
  clipAmt = 0.125f;
  filterCutoff = 400.0f;
  outputGain = juce::Decibels::decibelsToGain(-6.0f);
}

void Saturator::updateParams(apvts& tree) {
  const float _in =
      tree.getRawParameterValue(ID::SAT_inGain.toString())->load();
  const float _clip =
      tree.getRawParameterValue(ID::SAT_clipAmt.toString())->load();
  const float _freq =
      tree.getRawParameterValue(ID::SAT_outFilter.toString())->load();
  const float _out =
      tree.getRawParameterValue(ID::SAT_inGain.toString())->load();

  inputGain = juce::Decibels::decibelsToGain(_in);
  clipAmt = _clip;
  filterCutoff = _freq;
  filter.setFrequency(filterCutoff);
  outputGain = juce::Decibels::decibelsToGain(_out);
}

void Saturator::processChunk(float* data, int numSamples) {
  for (int i = 0; i < numSamples; ++i)
    data[i] = processSample(data[i]);
}

//----------------------------------------

float Saturator::processSample(float input) {
  // our thresholds for clipping
  static const float pThresh = juce::Decibels::decibelsToGain(-18.0f);
  static const float nThresh = -pThresh;
  // 1. apply input gain
  float s = input * inputGain;
  // 2. do the clipping
  if (!std::signbit(s) && s > pThresh) {
    s = pThresh + ((s - pThresh) * clipAmt);
  } else if (std::signbit(s) && s < nThresh) {
    s = nThresh - ((s - nThresh) * clipAmt);
  }
  // 3. filter
  s = filter.process(s);
  // 4. output gain
  return (s * outputGain);
}
