#ifndef INTEGER_H
#define INTEGER_H
#include "Menu.h"

namespace Campbell {
namespace menu {
struct Integer : public menu::Option {
  typedef int (Callbacks::*Callback)();
  // Shows number that is changeable with callback that is called if value
  // changes.
  template <typename T>
  Integer(Menu& parentMenu, int startNumber, T callback,
          bool isSelectable = true, bool isHighlighted = false)
      : Option(parentMenu, isSelectable, isHighlighted),
        parentMenu_(parentMenu),
        number(startNumber),
        callback_(static_cast<Callback>(callback)) {
    prefix = "<";
    suffix = ">";
  }
  ~Integer() {}

  const char* GetText() const {
    std::stringstream ss;
    ss << number;
    return ss.str().c_str();
  }
  // TODO: Make SELECT begin editing.
  menu::Input input(menu::Input input) {
    if (input == menu::LEFT || input == menu::RIGHT) {
      number += input == menu::LEFT ? -1 : 1;
      closeMenu();
      switch ((parentMenu_.GetCallbacks()->*callback_)()) {
        case 100:
          return QUIT;
        case 0:
          openMenu();
          return UNKONWN;
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
  int number;
  // The function to call when the button is selected.
  Callback callback_;
};
}  // namespace menu
}  // namespace Campbell
#endif /* ifndef INTEGER_H */
