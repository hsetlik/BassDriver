#pragma once
/* This file just includes juce and sets up a few
 * typedefs that I find handy in every juce project
 * */
#include "Identifiers.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"

typedef juce::Colour color_t;
typedef juce::Rectangle<float> rect_f;

constexpr float twoPi_f = juce::MathConstants<float>::twoPi;
//
// maybe we'll avoid writing 5 zillion 'prepare()' functions this way
namespace SampleRate {
void set(double rate);
double get();
}  // namespace SampleRate

inline float flerp(float a, float b, float t) {
  return a + ((b - a) * t);
}

inline bool fequal(float a, float b, float epsilon = 0.001f) {
  return std::fabs(a - b) < epsilon;
}

// thread-safe shorthand for reading apvts boolean params
bool readBoolTreeParam(apvts& tree, const juce::String& paramID);
