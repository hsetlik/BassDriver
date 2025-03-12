#include "BassDriver/Audio/EqualizerDSP.h"
#include "BassDriver/Audio/IIRFilter.h"
#include "BassDriver/Identifiers.h"
#include "juce_audio_basics/juce_audio_basics.h"

void SevenBandEQ::init(double sampleRate) {
  constexpr float bandFreqs[7] = {50.0f,  120.0f,  400.0f,  500.0f,
                                  800.0f, 4500.0f, 10000.0f};
  constexpr iir_type_t bandTypes[7] = {
      iir_type_t::HighPassQ, iir_type_t::LowShelf, iir_type_t::Peak,
      iir_type_t::Peak,      iir_type_t::Peak,     iir_type_t::HighShelf,
      iir_type_t::LowPassQ};

  for (size_t i = 0; i < 7; ++i) {
    auto params = *filters[i].getParams();
    params.frequency = bandFreqs[i];
    params.filterType = (uint8_t)bandTypes[i];
    params.q = 0.707f;
    params.gain = 1.0f;
    filters[i].setParams(params);
    filters[i].prepare(sampleRate);
  }
}

void SevenBandEQ::updateParams(apvts& tree) {
  for (size_t i = 0; i < 7; ++i) {
    juce::String id = "EQ_band" + juce::String(i + 1);
    const float _db = tree.getRawParameterValue(id)->load();
    filters[i].setGain(juce::Decibels::decibelsToGain(_db));
  }
  const float _outDb =
      tree.getRawParameterValue(ID::EQ_gain.toString())->load();
  outputGain = juce::Decibels::decibelsToGain(_outDb);
}

void SevenBandEQ::processChunk(float* buf, int numSamples) {
  for (int i = 0; i < numSamples; ++i)
    buf[i] = process(buf[i]);
}

//-------------------------------------------------------

float SevenBandEQ::process(float input) {
  float s = input;
  for (auto* it = filters.begin(); it != filters.end(); ++it) {
    s = it->process(s);
  }
  return (s * outputGain);
}
