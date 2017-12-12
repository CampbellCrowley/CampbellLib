#ifndef TEST_INPUT_H
#define TEST_INPUT_H
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
  ~TextInput() {}

  const char *GetText() const { return modifyableText.c_str(); }
  Menu::Input input(Menu::Input input) {
    switch (input) {
      case Menu::SELECT:
        modifyableText.clear();
        reprint();
        modifyableText = parentMenu.getString();
        return Menu::NONE;
      default:
        return input;
    }
  }

 private:
  Menu &parentMenu;
  std::string modifyableText;
};
}  // namespace Campbell
#endif /* ifndef TEST_INPUT_H */
