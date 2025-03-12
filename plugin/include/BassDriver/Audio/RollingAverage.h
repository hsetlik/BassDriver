#pragma once

#include "../Common.h"

// basic ring buffer class

class RingBuffer {
private:
  const int length;
  int head = 0;
  float* data;

public:
  RingBuffer(int size = 256) : length(size), data(new float[(size_t)size]) {
    for (int i = 0; i < length; ++i) {
      data[i] = 0.0f;
    }
  }
  ~RingBuffer() { delete[] data; }
  void push(float val) {
    data[head] = val;
    head = (head + 1) % length;
  }
  float& operator[](int idx) { return data[(head + idx) % length]; }
  float& getOldest() { return data[head]; }
};

//=========================================

class RollingAverage {
private:
  RingBuffer buf;
  float sum = 0.0f;
  float denom = 1.0f;

public:
  RollingAverage(int length);
  float process(float input);
};
