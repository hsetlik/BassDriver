#include "BassDriver/GUI/CompressorGraph.h"
#include "BassDriver/Identifiers.h"

CompressorGraph::CompressorGraph(Compressor* c)
    : comp(c), img(juce::Image::RGB, GRAPH_WIDTH, GRAPH_HEIGHT, true) {
  // zero out all the coord values
  for (int i = 0; i < GRAPH_WIDTH; ++i) {
    reductionPx.push(0);
    levelPx.push(GRAPH_HEIGHT - 1);
  }
  startTimerHz(45);
}

void CompressorGraph::timerCallback() {
  float level = comp->currentInputLevelDB();
  float red = comp->currentGainDB();
  updateImage(level, red);
  repaint();
}

void CompressorGraph::paint(juce::Graphics& g) {
  g.drawImageAt(img, 0, 0);
}

//=======================================================

void CompressorGraph::updateImage(float levelDb, float gainDb) {
  static const float redMax = -24.0f;
  const float rNorm = std::min(gainDb, 0.0f) / redMax;
  const int rPx = (int)(rNorm * 180.0f);
  reductionPx.push(rPx);
  // let's say we car about the input starting from
  // about -30 dB
  const float levelMin = -30.0f;
  levelDb = std::clamp(levelDb, levelMin, 0.0f);
  const float lNorm = (levelDb + 30.0f) / 30.0f;
  const int lPx = (int)(lNorm * 180.0f) + 1;
  levelPx.push(GRAPH_HEIGHT - lPx);

  // redraw the image
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
    while (y < GRAPH_HEIGHT) {
      img.setPixelAt(x, y, lvlColor);
      ++y;
    }
  }
}
