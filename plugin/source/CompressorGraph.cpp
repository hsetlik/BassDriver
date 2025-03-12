#include "BassDriver/GUI/CompressorGraph.h"

CompressorGraph::CompressorGraph(Compressor* c)
    : comp(c), img(juce::Image::RGB, GRAPH_WIDTH, GRAPH_WIDTH, true) {
  // zero out all the coord values
  for (int i = 0; i < GRAPH_WIDTH; ++i) {
    reductionPx.push(0);
    levelPx.push(GRAPH_WIDTH - 1);
  }
  startTimerHz(45);
}

void CompressorGraph::timerCallback() {
  float level = comp->currentInputLevelDB();
  float red = comp->currentGainReductionDB();
  updateImage(level, red);
  repaint();
}

void CompressorGraph::paint(juce::Graphics& g) {
  g.drawImageAt(img, 0, 0);
}

//=======================================================

void CompressorGraph::updateImage(float levelDb, float reductionDb) {
  float nReduction = reductionDb / -24.0f;
  int iReduction = (int)(nReduction * 80.0f);
  reductionPx.push(iReduction);
  int iLevel = (int)((levelDb / -24.0f) * 80.0f);
  levelPx.push(GRAPH_WIDTH - iLevel);
  // update the image
  static juce::Colour bkgnd(105, 105, 105);
  static juce::Colour lvlColor(64, 224, 208);
  static juce::Colour compColor(250, 128, 114);
  int y;
  for (int x = 0; x < GRAPH_WIDTH; ++x) {
    y = 0;
    while (y <= reductionPx[x]) {
      img.setPixelAt(x, y, compColor);
      ++y;
    }
    while (y <= levelPx[x]) {
      img.setPixelAt(x, y, bkgnd);
      ++y;
    }
    while (y < GRAPH_WIDTH) {
      img.setPixelAt(x, y, lvlColor);
      ++y;
    }
  }
}
