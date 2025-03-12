#pragma once
/* This namespace is where all the string identifiers for
 * parameters, components, and anything else should live.
 * Simply use the `DECLARE_ID` macro and never worry about
 * misspelling a string literal again.
 *
 * This translation unit is also responsible for the
 * `ID::getParameterLayout()` function which we use to set up
 * the AudioProcessorValueTreeState that runs everything
 * */
#include <juce_core/juce_core.h>
#include <juce_audio_processors/juce_audio_processors.h>

// typedefs bc some of these types are a mouthful
typedef juce::AudioProcessorValueTreeState apvts;
typedef std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
    slider_attach_ptr;
typedef std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
    combo_attach_ptr;
typedef std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
    button_attach_ptr;
typedef juce::NormalisableRange<float> frange_t;

#define DECLARE_ID(name) const juce::Identifier name(#name);

frange_t rangeWithCenter(float start, float end, float center);
namespace ID {
// top level ID for the apvts
DECLARE_ID(BassDriver_state)

// Dry/common controls
DECLARE_ID(dryLevel)
DECLARE_ID(stageOrder)
DECLARE_ID(preampGain)

// EQ stage-----------------------
DECLARE_ID(EQ_active)
DECLARE_ID(EQ_band1)
DECLARE_ID(EQ_band2)
DECLARE_ID(EQ_band3)
DECLARE_ID(EQ_band4)
DECLARE_ID(EQ_band5)
DECLARE_ID(EQ_band6)
DECLARE_ID(EQ_band7)
DECLARE_ID(EQ_gain)

// Saturation stage-----------------------
DECLARE_ID(SAT_active)
DECLARE_ID(SAT_inGain)
DECLARE_ID(SAT_clipAmt)
DECLARE_ID(SAT_outFilter)
DECLARE_ID(SAT_outGain)

// Compression stage----------------------
DECLARE_ID(COMP_active)
DECLARE_ID(COMP_inGain)
DECLARE_ID(COMP_thresh)
DECLARE_ID(COMP_ratio)
DECLARE_ID(COMP_attack)
DECLARE_ID(COMP_release)
DECLARE_ID(COMP_outGain)

apvts::ParameterLayout getParameterLayout();
}  // namespace ID

#undef DECLARE_ID
