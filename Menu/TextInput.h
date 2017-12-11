#include <curses.h>
#include <string>
#include "Menu.h"

namespace Campbell {
struct TextInput : public Menu::Option {
  // Shows text input for entering a string. No callback, since everything is
  // managed internally.
  TextInput(Menu &parentMenu, std::string defaultText = "",
            bool isSelectable = true, bool isHighlighted = false)
      : Option(parentMenu, isSelectable, isHighlighted),
        parentMenu(parentMenu),
        modifyableText(defaultText) {
    prefix = "[";
    suffix = "]";
  }

  const char *GetText() const { return modifyableText.c_str(); }
  Menu::Input input(Menu::Input input) {
    switch(input) {
      case Menu::SELECT:
        modifyableText.clear();
        reprint();
        modifyableText = parentMenu.getString();
        return Menu::NONE;
      default:
        return input;
    }
  }
  Menu &parentMenu;
  std::string modifyableText;
};
}  // namespace Campbell
