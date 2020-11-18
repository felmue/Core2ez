#include "ezButton.h"
#include <ezRoot.h>

ezRadiobutton::ezRadiobutton(ezWidget& parentWidget,
                             int16_t x_ /* = EZ_INVALID */,
                             int16_t y_ /* = EZ_INVALID */,
                             int16_t w_ /* = 0 */, int16_t h_ /* = 0 */,
                             String text_ /* = "" */,
                             bool value_ /* = false */,
                             WidgetColors colors_ /* = THEME_COLORS */,
                             const GFXfont* font_ /* = THEME_FONT */) {
  init(&parentWidget, x_, y_, w_, h_, text_, value_, colors_, font_);
}

ezRadiobutton::ezRadiobutton(int16_t x_ /* = EZ_INVALID */,
                             int16_t y_ /* = EZ_INVALID */,
                             int16_t w_ /* = 0 */, int16_t h_ /* = 0 */,
                             String text_ /* = "" */,
                             bool value_ /* = false */,
                             WidgetColors colors_ /* = THEME_COLORS */,
                             const GFXfont* font_ /* = THEME_FONT */) {
  init(nullptr, x_, y_, w_, h_, text_, value_, colors_, font_);
}

void ezRadiobutton::init(ezWidget* pwPtr,
                         int16_t x_, int16_t y_, int16_t w_, int16_t h_,
                         String text_, bool value_, WidgetColors colors_,
                         const GFXfont* font_) {
  type       = W_RADIOBUTTON;
  set(x_, y_, w_, h_);
  colors     = ez.Theme.colors(colors_,   ez.Theme.rdb_colors);
  value      = value_;
  label.font = (font_ != THEME_FONT) ? font_ : ez.Theme.rdb_font;
  label.text = text_;
  add(label);
  if (pwPtr) pwPtr->add(*this); else ez.Screen.add(*this);
}


ezRadiobutton::operator bool() { return value; }

ezRadiobutton& ezRadiobutton::operator=(bool value_) {
  value = value_;
  return *this;
}

void ezRadiobutton::draw() {

  if (!colors) return;

  valueDraw();

  drawCircle(h / 2, h / 2, h / 2, colors.outline);

  label.colors.text = colors.text;
  label.align = EZ_LEFT;
  uint8_t margin = h / 4;
  label.set(h + margin, 0, w - (h + margin), h);

  drawChildren();
}

void ezRadiobutton::eventPost() {
  if (ez.e.widget == this && ez.e == E_TAP) {
    if (!value) {
      if (_parent) static_cast<ezWidget*>(_parent)->turnOffRadiobuttons();
      value = true;
      valueDraw();
      refresh();
    }
  }
}

void ezRadiobutton::valueDraw() {
  fillCircle(h / 2, h / 2, h / 4, value ? colors.text : colors.fill);
}