#include "BassDriver/Audio/MasterDSP.h"
#include "BassDriver/Common.h"
#include "BassDriver/Identifiers.h"

void BassDriverCore::init(double sampleRate) {
  sat.init(sampleRate);
  comp.init(sampleRate);
}

void BassDriverCore::updateParams(apvts& tree) {
  const float _preGain =
      tree.getRawParameterValue(ID::preampGain.toString())->load();
  const bool _order = readBoolTreeParam(tree, ID::stageOrder.toString());
  const bool _satOn = readBoolTreeParam(tree, ID::SAT_active.toString());
  const bool _compOn = readBoolTreeParam(tree, ID::COMP_active.toString());

  inputGain = _preGain;

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
}

void BassDriverCore::applyInputGain(float* buf, int numSamples) {
  for (int i = 0; i < numSamples; ++i) {
    buf[i] *= inputGain;
  }
}

void BassDriverCore::processChunk(float* data, int numSamples) {
  applyInputGain(data, numSamples);
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
}
