#include "Menu.h"

namespace Campbell {
struct Button : public Menu::Option {
  // Shows selectable option with title and callback.
  Button(Menu& parentMenu, const char* text, const Callbacks callback,
         bool isSelectable = true, bool isHighlighted = false)
      : Option(parentMenu, isSelectable, isHighlighted),
        text_(text),
        callback_(callback) {
    prefix = "";
    suffix = "";
  }
  const char* GetText() const { return text_; }
  Menu::Input input(Menu::Input input) {
    if (input == Menu::SELECT) {
      closeMenu();
      switch(callback_.callback()) {
          case 0:
            openMenu();
            return Menu::UNKONWN;
          case 100:
            return Menu::QUIT;
          case 1:
          default:
            openMenu();
            return Menu::NONE;
      }
    }
    return input;
  }

  // Text to show the user.
  const char* text_;
  // The function to call when the button is selected.
  const Callbacks callback_;
};
}  // namespace Campbell
