#include "BassDriver/Identifiers.h"
#include <memory>
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_processors/juce_audio_processors.h"
frange_t rangeWithCenter(float start, float end, float center) {
  frange_t range(start, end);
  range.setSkewForCentre(center);
  return range;
}
// constexpr version of the above for compile time optimizations

apvts::ParameterLayout ID::getParameterLayout() {
  apvts::ParameterLayout layout;
  // add your parameters here
  const float negInfinity = -120.0f;
  const float _dryMax = -6.0f;
  const float _dryCenter = -24.0f;
  frange_t dryRange = rangeWithCenter(negInfinity, _dryMax, _dryCenter);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::dryLevel.toString(), "Dry Level", dryRange, _dryCenter));

  const float preGainMin = -3.0f;
  const float preGainMax = 12.0f;
  const float preGainDefault = 3.0f;
  frange_t preGainRange =
      rangeWithCenter(preGainMin, preGainMax, preGainDefault);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::preampGain.toString(), "Pre-gain", preGainRange, preGainDefault));
  // true = comp. first, false = sat. first
  layout.add(std::make_unique<juce::AudioParameterBool>(
      ID::stageOrder.toString(), "Effect Order", true));

  // Equalizer params-------------------------------------

  layout.add(std::make_unique<juce::AudioParameterBool>(
      ID::EQ_active.toString(), "EQ On", true));
  const float eqBandDefault = 0.0f;
  frange_t eqRange = rangeWithCenter(-15.0f, 15.0f, eqBandDefault);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::EQ_band1.toString(), "50Hz", eqRange, eqBandDefault));
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::EQ_band2.toString(), "120Hz", eqRange, eqBandDefault));
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::EQ_band3.toString(), "400Hz", eqRange, eqBandDefault));
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::EQ_band4.toString(), "500Hz", eqRange, eqBandDefault));
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::EQ_band5.toString(), "800Hz", eqRange, eqBandDefault));
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::EQ_band6.toString(), "4.5kHz", eqRange, eqBandDefault));
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::EQ_band7.toString(), "10kHz", eqRange, eqBandDefault));
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::EQ_gain.toString(), "Gain", eqRange, eqBandDefault));

  // Saturation params---------------------------------------------
  layout.add(std::make_unique<juce::AudioParameterBool>(
      ID::SAT_active.toString(), "Drive On", true));
  const float satInMin = -24.0f;
  const float satInMax = 60.0f;
  const float satInCenter = 15.0f;
  frange_t satInRange = rangeWithCenter(satInMin, satInMax, satInCenter);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::SAT_inGain.toString(), "Gain", satInRange, 0.0f));

  const float clipDefault = 0.125f;
  frange_t clipRange = rangeWithCenter(-1.0f, 1.0f, clipDefault);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::SAT_clipAmt.toString(), "Drive", clipRange, clipDefault));

  const float satFilterMin = 240.0f;
  const float satFilterMax = 1100.0f;
  const float satFilterDefault = 400.0f;
  frange_t satFilterRange =
      rangeWithCenter(satFilterMin, satFilterMax, satFilterDefault);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::SAT_outFilter.toString(), "Tone", satFilterRange, satFilterDefault));

  const float satOutMin = -34.0f;
  const float satOutDefault = -6.0f;
  frange_t satOutRange = rangeWithCenter(satOutMin, 0.0f, satOutDefault);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::SAT_outGain.toString(), "Output Gain", satOutRange, satOutDefault));

  //  Compression Params---------------------------------------------
  layout.add(std::make_unique<juce::AudioParameterBool>(
      ID::COMP_active.toString(), "Compressor On", true));

  const float compInMax = 6.0f;
  const float compInMin = -24.0f;
  const float compInDefault = 0.0f;
  frange_t compInRange = rangeWithCenter(compInMin, compInMax, compInDefault);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::COMP_inGain.toString(), "In gain", compInRange, compInDefault));

  const float threshMax = -3.0f;
  const float threshMin = -36.0f;
  const float threshDefault = -20.0f;
  frange_t threshRange = rangeWithCenter(threshMin, threshMax, threshDefault);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::COMP_thresh.toString(), "Threshold", threshRange, threshDefault));

  const float ratioMin = 0.85f;
  const float ratioMax = 10.0f;
  const float ratioDefault = 1.5f;
  frange_t ratioRange = rangeWithCenter(ratioMin, ratioMax, ratioDefault);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::COMP_ratio.toString(), "Ratio", ratioRange, ratioDefault));

  const float atkDefault = 0.125f;
  frange_t atkRange = rangeWithCenter(0.0f, 1.0f, atkDefault);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::COMP_attack.toString(), "Attack", atkRange, atkDefault));

  const float releaseDefault = 0.3f;
  frange_t releaseRange = rangeWithCenter(0.0f, 1.0f, releaseDefault);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::COMP_release.toString(), "Release", releaseRange, releaseDefault));

  const float compOutMin = -18.0f;
  const float compOutMax = 12.0f;
  frange_t compOutRange = rangeWithCenter(compOutMin, compOutMax, 0.0f);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::COMP_outGain.toString(), "Out gain", compOutRange, 0.0f));

  return layout;
}
