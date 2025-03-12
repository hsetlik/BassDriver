#include "BassDriver/Audio/MasterDSP.h"
#include "BassDriver/Common.h"
#include "BassDriver/Identifiers.h"
#include "juce_audio_basics/juce_audio_basics.h"

void BassDriverCore::init(double sampleRate) {
  sat.init(sampleRate);
  comp.init(sampleRate);
  eq.init(sampleRate);
}

void BassDriverCore::updateParams(apvts& tree) {
  const float _preGain =
      tree.getRawParameterValue(ID::preampGain.toString())->load();
  const float _dryLevel =
      tree.getRawParameterValue(ID::dryLevel.toString())->load();
  const bool _order = readBoolTreeParam(tree, ID::stageOrder.toString());
  const bool _satOn = readBoolTreeParam(tree, ID::SAT_active.toString());
  const bool _compOn = readBoolTreeParam(tree, ID::COMP_active.toString());
  const bool _eqOn = readBoolTreeParam(tree, ID::EQ_active.toString());

  inputGain = juce::Decibels::decibelsToGain(_preGain);
  dryGain = juce::Decibels::decibelsToGain(_dryLevel);

  eqActive = _eqOn;
  // translate to config enum
  if (_satOn && _compOn) {
    config = _order ? stage_config::bothCompFirst : stage_config::bothSatFirst;
  } else if (_satOn) {
    config = stage_config::satOnly;
  } else if (_compOn) {
    config = stage_config::compOnly;
  } else {
    config = stage_config::neither;
  }

  sat.updateParams(tree);
  comp.updateParams(tree);
  eq.updateParams(tree);
}

void BassDriverCore::applyInputGain(float* buf, int numSamples) {
  for (int i = 0; i < numSamples; ++i) {
    buf[i] *= inputGain;
  }
}

void BassDriverCore::copyDryBuffer(float* buf, int numSamples) {
  std::memcpy(dryBuf, buf, (size_t)numSamples * sizeof(float));
}
void BassDriverCore::addDryMix(float* buf, int numSamples) {
  for (int i = 0; i < numSamples; ++i) {
    buf[i] += (dryBuf[i] * dryGain);
  }
}

void BassDriverCore::processChunk(float* data, int numSamples) {
  applyInputGain(data, numSamples);
  copyDryBuffer(data, numSamples);
  switch (config) {
    case stage_config::bothCompFirst:
      comp.processChunk(data, numSamples);
      sat.processChunk(data, numSamples);
      break;
    case stage_config::bothSatFirst:
      sat.processChunk(data, numSamples);
      comp.processChunk(data, numSamples);
      break;
    case stage_config::satOnly:
      sat.processChunk(data, numSamples);
      break;
    case stage_config::compOnly:
      comp.processChunk(data, numSamples);
      break;
    case stage_config::neither:
      break;
    default:
      break;
  }
  if (eqActive) {
    eq.processChunk(data, numSamples);
  }
  addDryMix(data, numSamples);
}
