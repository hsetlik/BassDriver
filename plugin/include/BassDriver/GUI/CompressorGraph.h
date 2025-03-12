#pragma once
#include "../Common.h"
#include "BassDriver/Audio/CompressorDSP.h"

#define GRAPH_WIDTH 400
#define GRAPH_HEIGHT 360

// simple ring buffer to hold our gain data
class RingBuf {
private:
  int data[GRAPH_WIDTH];
  int head = 0;

public:
  RingBuf() = default;
  void push(int value) {
    data[head] = value;
    head = (head + 1) % GRAPH_WIDTH;
  }
  int& operator[](int idx) { return data[(head + idx) % GRAPH_WIDTH]; }
};

class CompressorGraph : public juce::Component, juce::Timer {
private:
  Compressor* const comp;
  juce::Image img;
  RingBuf levelPx;
  RingBuf reductionPx;
  void updateImage(float levelDb, float reductionDb);

public:
  CompressorGraph(Compressor* c);
  void timerCallback() override;
  void paint(juce::Graphics& g) override;
};
