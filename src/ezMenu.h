#ifndef _EZMENU_H_
#define _EZMENU_H_

#include <ezHeader.h>
#include <ezWindow.h>
#include <ezList.h>
#include <ezValues.h>

struct ezMenuItem {
  String                  text;
  void                    (*func)();
};

class ezMenu {

 public:
  static int16_t            retval;
  static ezMenu*            caller;

  WidgetColors              colors;
  WidgetColors              onColors;
  ezFont                    font;

  int16_t                   itemsPerRow     = EZ_AUTO;
  int16_t                   rowsPerScreen   = EZ_AUTO;
  int16_t                   margin          =  8;
  int16_t                   cornerRadius    =  8;

                            ezMenu(String title_,
                                   WidgetColors colors_   = THEME_COLORS,
                                   WidgetColors onColors_ = THEME_COLORS,
                                   ezFont font_           = THEME_FONT);
  void                      addItem(String text_);
  void                      addItem(String text_, void (*func_)());
  int16_t                   doMenu();
  int16_t                   run(bool noBreak = false);
  int16_t                   runOnce();
  int16_t                   selected = EZ_INVALID;
  String                    title;
  std::vector<ezMenuItem>   items;

};

void ezBreak();
void ezBack();

#endif /* _EZMENU_H_ */
