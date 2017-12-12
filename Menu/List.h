#ifndef LIST_H
#define LIST_H
#include <vector>
#include "Menu.h"

namespace Campbell {
struct List : public Menu::Option {
  // Allows a choice between a list of options.
  List(Menu &parentMenu, const char *text,
       const std::vector<std::string> &values, bool isSelectable = true,
       bool isHighlighted = false)
      : Option(parentMenu, isSelectable, isHighlighted),
        text_(text),
        values(values) {
    currentValue = 0;
    prefix = ": <";
    suffix = ">";
  }
  ~List() {}

  const char *GetText() const {
    if (currentValue < values.size()) {
      return values[currentValue].c_str();
    } else {
      return "Oops, this is broken.";
    }
  }

  Menu::Input input(Menu::Input input) {
    if ((currentValue < values.size() - 1 && input == Menu::RIGHT) ||
        (currentValue > 0 && input == Menu::LEFT)) {
      currentValue += input == Menu::LEFT ? -1 : 1;
      return Menu::NONE;
    }
    return input;
  }

 private:
  const char *text_;
  const std::vector<std::string> values;
  unsigned int currentValue;
};
}  // namespace Campbell
#endif /* ifndef LIST_H */
