#ifndef CAMPBELL_MENU_BUTTON_H
#define CAMPBELL_MENU_BUTTON_H
#include "Menu.h"

namespace Campbell {
namespace menu {
struct Button : public Option {
  typedef int (Callbacks::*Callback)();
  // Shows selectable option with title and callback.
  template <typename T>
  Button(Menu& parentMenu, const char* text, T callback,
         bool isSelectable = true, bool isHighlighted = false)
      : Option(parentMenu, isSelectable, isHighlighted),
        parentMenu_(parentMenu),
        text_(text),
        callback_(static_cast<Callback>(callback)) {
    prefix = "";
    suffix = "";
  }
  ~Button() {}

  const char* GetText() const { return text_; }
  Input input(Input input) {
    if (input == SELECT) {
      closeMenu();
      switch ((parentMenu_.GetCallbacks()->*callback_)()) {
        case 0:
          openMenu();
          return UNKONWN;
        case 100:
          return QUIT;
        case 1:
        default:
          openMenu();
          return NONE;
      }
    }
    return input;
  }

 private:
  Menu& parentMenu_;
  // Text to show the user.
  const char* text_;
  // The function to call when the button is selected.
  Callback callback_;
};
}  // namespace menu
}  // namespace Campbell
#endif /* ifndef CAMPBELL_MENU_BUTTON_H */
