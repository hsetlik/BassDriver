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
  const float _dryMax = juce::Decibels::decibelsToGain(-6.0f);
  const float _dryCenter = juce::Decibels::decibelsToGain(-24.0f);
  frange_t dryRange = rangeWithCenter(0.0f, _dryMax, _dryCenter);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::dryLevel.toString(), "Dry Level", dryRange, _dryCenter));

  const float preGainMin = juce::Decibels::decibelsToGain(-3.0f);
  const float preGainMax = juce::Decibels::decibelsToGain(9.0f);
  const float preGainDefault = 1.0f;
  frange_t preGainRange =
      rangeWithCenter(preGainMin, preGainMax, preGainDefault);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::preampGain.toString(), "Pre-gain", preGainRange, preGainDefault));
  // true = comp. first, false = sat. first
  layout.add(std::make_unique<juce::AudioParameterBool>(
      ID::stageOrder.toString(), "Effect Order", true));

  // Saturation params---------------------------------------------
  layout.add(std::make_unique<juce::AudioParameterBool>(
      ID::SAT_active.toString(), "Drive On", true));
  const float satInMin = juce::Decibels::decibelsToGain(-24.0f);
  const float satInMax = juce::Decibels::decibelsToGain(60.0f);
  const float satInCenter = juce::Decibels::decibelsToGain(15.0f);
  frange_t satInRange = rangeWithCenter(satInMin, satInMax, satInCenter);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::SAT_inGain.toString(), "Gain", satInRange, satInCenter));

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

  const float satOutMin = juce::Decibels::decibelsToGain(-34.0f);
  const float satOutDefault = juce::Decibels::decibelsToGain(-6.0f);
  frange_t satOutRange = rangeWithCenter(satOutMin, 1.0f, satOutDefault);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::SAT_outGain.toString(), "Output Gain", satOutRange, satOutDefault));

  //  Compression Params---------------------------------------------
  layout.add(std::make_unique<juce::AudioParameterBool>(
      ID::COMP_active.toString(), "Compressor On", true));

  const float compInMax = juce::Decibels::decibelsToGain(6.0f);
  const float compInMin = juce::Decibels::decibelsToGain(-24.0f);
  const float compInDefault = 1.0f;
  frange_t compInRange = rangeWithCenter(compInMin, compInMax, compInDefault);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::COMP_inGain.toString(), "In gain", compInRange, compInDefault));

  const float threshMax = juce::Decibels::decibelsToGain(-3.0f);
  const float threshMin = juce::Decibels::decibelsToGain(-36.0f);
  const float threshDefault = juce::Decibels::decibelsToGain(-20.0f);
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

  const float compOutMin = juce::Decibels::decibelsToGain(-18.0f);
  const float compOutMax = juce::Decibels::decibelsToGain(10.0f);
  frange_t compOutRange = rangeWithCenter(compOutMin, compOutMax, 1.0f);
  layout.add(std::make_unique<juce::AudioParameterFloat>(
      ID::COMP_outGain.toString(), "Out gain", compOutRange, 1.0f));

  return layout;
}
