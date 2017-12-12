#ifndef LIST_H
#define LIST_H
#include <vector>
#include "Menu.h"

namespace Campbell {
namespace menu {
struct List : public menu::Option {
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

  Input input(Input input) {
    if ((currentValue < values.size() - 1 && input == RIGHT) ||
        (currentValue > 0 && input == LEFT)) {
      currentValue += input == LEFT ? -1 : 1;
      return NONE;
    }
    return input;
  }

 private:
  const char *text_;
  const std::vector<std::string> values;
  unsigned int currentValue;
};
}  // namespace menu
}  // namespace Campbell
#endif /* ifndef LIST_H */
