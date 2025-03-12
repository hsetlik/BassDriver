#pragma once
#include "../Common.h"
#include "juce_graphics/juce_graphics.h"
#include <FontBinary.h>

typedef juce::Typeface::Ptr typeface_ptr;

namespace BDFont {
// enum of all the fonts
enum fontID {
  arialNarrow,
  kenyanCoffeeRg,
  kenyanCoffeeIt,
  bebasNeue,
  highwayGothicCd
};

#define NUM_BD_FONTS 5

// some optimization & wrapping for
// the binary-loading of the fonts
juce::Font getFont(int id, float size = 12.0f);
}  // namespace BDFont

//=============================================================================
