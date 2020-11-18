#ifndef _EZWIDGET_H_
#define _EZWIDGET_H_

#include <ezEvents.h>
#include <ezDisplayZone.h>


// Special color value, meaning we don't draw anything
#define NODRAW            0x0120

enum widget_t {
  W_WIDGET,
  W_ROOT,
  W_WINDOW,
  W_BUTTON,
  W_LABEL,
  W_CHECKBOX,
  W_RADIOBUTTON,
  W_INPUT
};


struct WidgetColors {
  bool operator==(WidgetColors a) {
    return (a.fill == fill && a.text == text && a.outline == outline);
  }
  bool operator!=(WidgetColors a) {
    return !(*this == a);
  }
  explicit operator bool() {
    return (fill != NODRAW || text != NODRAW || outline != NODRAW);
  }
  uint16_t                fill;
  uint16_t                text;
  uint16_t                outline;
};

class ezWidget : public ezDisplayZone, public Eventful {
 public:
  ezWidget*               parent();
  const char*             typeName();
  virtual void            add(ezWidget& w);
  virtual void            remove(ezWidget& w);
  virtual void            add(ezGesture& g);
  virtual void            remove(ezGesture& g);
  virtual void            push();
  uint16_t                parentFill();
  void                    turnOffRadiobuttons();
  void                    event();
  virtual void            clear();
  virtual void            draw();
  void                    drawChildren();
  void                    spriteBuffer(int16_t w_ = -1, int16_t h_ = -1);
  virtual void            eventPre();
  virtual void            eventPost();
  virtual void            cancel();
  bool                    isPressed();
  bool                    isReleased();
  bool                    wasPressed();
  bool                    wasReleased();

  widget_t                type            = W_WIDGET;
  WidgetColors            colors          = {TFT_WHITE, TFT_BLACK, TFT_BLACK};
  bool                    numb            = false;
  uint16_t                tapTime         = 200;
  uint16_t                dbltapTime      = 200;
  uint16_t                longPressTime   =   0;
  uint16_t                repeatDelay     =   0;
  uint16_t                repeatInterval  = 150;
  uint16_t                userData        =   0;
  bool                    glissando       = false;
  bool                    scroll          = true;
  bool                    showArrows      = true;

 protected:
  friend class ezWindow;
  void                    _eventProcess();
  void                    _updateBox();
  void                    _drawArrow(int16_t direction);
  std::vector<ezWidget*>  _widgets;
  std::vector<ezGesture*> _gestures;
  bool                    _state          = false;
  bool                    _changed        = false;
  bool                    _tapWait        = false;
  bool                    _pressing       = false;
  bool                    _longPressing   = false;
  bool                    _cancelled      = false;
  bool                    _touched[2]     = {false, false};
  uint32_t                _lastRepeat     = 0;
  uint32_t                _lastOnTime     = 0;
  uint32_t                _lastOffTime    = 0;
  Event                   _lastOnEvent    = Event();
  Event                   _lastOffEvent   = Event();
};

#endif /* _EZWIDGET_H_ */
