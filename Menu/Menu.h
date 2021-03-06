#ifndef CAMPBELL_MENU_MENU_H
#define CAMPBELL_MENU_MENU_H
#include <sstream>
#include <vector>
#include "../CampbellLib.h"

namespace Campbell {

// Class in that should be instantiated and passed in as argument for option
// callbacks.
struct Callbacks {
  virtual int nothing() { return 1; }
  virtual int quit() { return 100; }
  virtual int error() { return 0; }

 protected:
  Callbacks() {}
};

namespace menu {

// Forawrd declaration
class Option;

// Available inputs.
enum Input { UP, DOWN, LEFT, RIGHT, SELECT, QUIT, NONE, UNKONWN };
// Color pair indexes.
enum Colors {
  HIGHLIGHTED = 50,
  NORMAL,
  TITLE,
  INSTRUCTIONS,
  BACKGROUND,
  ERROR,
  DISABLED
};


// TODO: Find solution for when the window is too small to fit all options.
// TODO: Allow for 2D menu. Not just a list.
class Menu {
 public:
  Menu(Callbacks* callbacks, const char* title = "")
      : title(title), callbacks_(callbacks) {
    isWinOpen_ = false;
    currentIndex = 0;
  }
  Menu(const char* title = "") : title(title) {
    isWinOpen_ = false;
    currentIndex = 0;
  }
  ~Menu() { endWin(); }

  // Opens menu and takes over control flow.
  void startMenu();
  // Opens the menu but does not take over control flow.
  void openMenu();
  // Prints the menu to the open screen.
  void printMenu() const;
  // Closes the menu.
  void closeMenu();
  // Starts curses session
  void startWin();
  // Ends curses session
  void endWin();
  // Move the current selection in the requested direction. Returns if actually
  // moved or if screen needs to be reprinted.
  bool move(Input direction);

  // Adds an option to the menu list.
  void AddOption(Option* newOption);
  void clearOptions() { optionList.clear(); }

  // Returns whether the menu is open or not.
  bool isWinOpen() const { return isWinOpen_; }
  // Returns list of current options.
  std::vector<Option*>& getOptionList() { return optionList; }
  int getCurrentIndex() const { return currentIndex; }

  // Get text input via curses screen.
  std::string getString() const;

  Callbacks* GetCallbacks() const { return callbacks_; }

 protected:
  // Gets the user's input.
  Input getInput() const;
  // Get the next Option that isSelectable in the given direction.
  int getNextIndex(Input direction) const;

  // Set current color in ncurses.
  void setColor(Colors index) const;
  void unsetColor(Colors index) const;

 private:
  // Current selected menu option index in option list.
  int currentIndex;
  // Stores whether the window is open or not.
  bool isWinOpen_;
  // List of all options to show in the menu.
  std::vector<Option*> optionList;
  // Title to show at the top before the options.
  const char* title;
  // The callback container for this menu.
  Callbacks* callbacks_;
};  // class Menu

// An option to show in the menu list. Must be inherited to be used.
class Option {
 public:
  // Returns formatted c-style string for showing the user.
  virtual const char* GetText() const { return "NOT IMPLEMENTED"; }
  // Gets input direction sent to this option. Returned Input is processed
  // again.
  virtual Campbell::menu::Input input(Campbell::menu::Input input) {
    return input;
  }

  // Prefix and suffix to surround GetText with.
  const char* GetPrefix() const { return prefix; }
  const char* GetSuffix() const { return suffix; }

  // Whether or not the option can be selected.
  bool isSelectable_;
  // If the option is highlighted.
  bool isHighlighted_;

 protected:
  Option(Menu& parentMenu, bool isSelectable, bool isHighlighted)
      : parentMenu(parentMenu) {
    isSelectable_ = isSelectable;
    isHighlighted_ = isHighlighted;
    prefix = "";
    suffix = "";
  }
  // virtual ~Option() {}
  const char* prefix;
  const char* suffix;

  void reprint() const { parentMenu.printMenu(); }
  void closeMenu() { parentMenu.closeMenu(); }
  void openMenu() { parentMenu.openMenu(); }

 private:
  Menu& parentMenu;
};
}  // namespace menu
}  // namespace Campbell

#endif  // ifndef CAMPBELL_MENU_MENU_H
