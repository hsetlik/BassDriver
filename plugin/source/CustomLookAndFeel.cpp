#include "BassDriver/GUI/CustomLookAndFeel.h"
#include "FontBinary.h"

namespace BDFont {
static typeface_ptr loadTypeface(fontID id) {
  typeface_ptr ptr;
  switch (id) {
    case arialNarrow:
      ptr = juce::Typeface::createSystemTypefaceFor(
          FontBinary::arial_narrow_ttf, FontBinary::arial_narrow_ttfSize);
      break;
    case kenyanCoffeeRg:
      ptr = juce::Typeface::createSystemTypefaceFor(
          FontBinary::kenyan_coffee_rg_otf,
          FontBinary::kenyan_coffee_rg_otfSize);
      break;
    case kenyanCoffeeIt:
      ptr = juce::Typeface::createSystemTypefaceFor(
          FontBinary::kenyan_coffee_rg_it_otf,
          FontBinary::kenyan_coffee_rg_it_otfSize);
      break;
    case bebasNeue:
      ptr = juce::Typeface::createSystemTypefaceFor(
          FontBinary::bebas_neue_rg_otf, FontBinary::bebas_neue_rg_otfSize);
      break;
    case highwayGothicCd:
      ptr = juce::Typeface::createSystemTypefaceFor(
          FontBinary::highway_gothic_condensed_ttf,
          FontBinary::highway_gothic_condensed_ttfSize);
      break;
    default:
      ptr = juce::Typeface::createSystemTypefaceFor(
          FontBinary::highway_gothic_condensed_ttf,
          FontBinary::highway_gothic_condensed_ttfSize);
      break;
  }
  return ptr;
}

static std::array<typeface_ptr, NUM_BD_FONTS> getBdTypefaces() {
  std::array<typeface_ptr, NUM_BD_FONTS> arr;
  for (size_t i = 0; i < NUM_BD_FONTS; ++i) {
    arr[i] = loadTypeface((fontID)i);
  }
  return arr;
}
//-------------------------------
juce::Font getFont(int id, float size) {
  static std::array<typeface_ptr, NUM_BD_FONTS> typefaces = getBdTypefaces();
  auto opts = juce::FontOptions(typefaces[(size_t)id]);
  juce::Font font(opts);
  font.setHeight(size);
  return font;
}

}  // namespace BDFont
