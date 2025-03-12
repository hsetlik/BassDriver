#include "BassDriver/GUI/EqualizerPanel.h"
#include "BassDriver/Common.h"
#include "BassDriver/GUI/CustomLookAndFeel.h"
#include "BassDriver/GUI/ParamSlider.h"
#include "BassDriver/Identifiers.h"

EqualizerPanel::EqualizerPanel(apvts& tree) {
  // initialize the 7 band sliders
  for (int i = 0; i < 7; ++i) {
    juce::String id = "EQ_band" + juce::String(i + 1);
    auto* s = sliders.add(new LabeledParamSlider(tree, id));
    addAndMakeVisible(s);
  }
  // initialize the last gain slider
  auto* g = sliders.add(new LabeledParamSlider(tree, ID::EQ_gain.toString()));
  addAndMakeVisible(g);
}

void EqualizerPanel::resized() {
  auto fBounds = getLocalBounds().toFloat();
  const float h = fBounds.getHeight();
  const float w = fBounds.getWidth() / (float)sliders.size();
  for (int i = 0; i < sliders.size(); ++i) {
    rect_f bounds(w * (float)i, 10.0f, w, h - 20.0f);
    sliders[i]->setBounds(bounds.toNearestInt());
  }
}

void EqualizerPanel::paint(juce::Graphics& g) {
  auto fBounds = getLocalBounds().toFloat();
  static const color_t border = BDColor::darkGrayBkgnd;
  static const color_t fill = BDColor::fillGrayDark;
  g.setColour(border);
  g.fillRect(fBounds);
  g.setColour(fill);
  g.fillRect(fBounds.reduced(6.0f));
}
