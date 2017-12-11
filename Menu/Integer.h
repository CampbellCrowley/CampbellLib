#include "Menu.h"

namespace Campbell {
struct Integer : public Menu::Option {
  // Shows number that is changeable with callback that is called if value
  // changes.
  Integer(Menu& parentMenu, int startNumber, const Callbacks callback,
          bool isSelectable = true, bool isHighlighted = false)
      : Option(parentMenu, isSelectable, isHighlighted),
        number(startNumber),
        callback_(callback) {
    prefix = "<";
    suffix = ">";
  }

  const char* GetText() const {
    std::stringstream ss;
    ss << number;
    return ss.str().c_str();
  }
  // TODO: Make SELECT begin editing.
  Menu::Input input(Menu::Input input) {
    if (input == Menu::LEFT || input == Menu::RIGHT) {
      number += input == Menu::LEFT ? -1 : 1;
      closeMenu();
      switch (callback_.callback()) {
        case 100:
          return Menu::QUIT;
        case 0:
          openMenu();
          return Menu::UNKONWN;
        case 1:
        default:
          openMenu();
          return Menu::NONE;
      }
    }
    return input;
  }

  // Text to show the user.
  int number;
  // The function to call when the button is selected.
  const Callbacks callback_;
};
}  // namespace Campbell
