#pragma once
#include "../Common.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include <FontBinary.h>

typedef juce::Typeface::Ptr typeface_ptr;
typedef juce::LookAndFeel_V4::ColourScheme::UIColour ui_color_t;

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

// easy storage for all our RGB color objects
namespace BDColor {
const color_t darkGrayBkgnd(56, 56, 57);
const color_t fillGrayDark(87, 87, 86);
const color_t fillGrayMid(102, 101, 102);
const color_t fillGrayLight(134, 134, 134);

}  // namespace BDColor

//=============================================================================

/* Override the various LookAndFeelMethods
 * to draw components differently
 * */

class BassDriverLnF : public juce::LookAndFeel_V4 {
public:
  BassDriverLnF();
};
