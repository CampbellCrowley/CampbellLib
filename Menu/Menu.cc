#include "Menu.h"
#include <curses.h>
namespace Campbell {
namespace menu {
void Menu::startMenu() {
  openMenu();
  Input nextInput = NONE;
  while (nextInput != QUIT && isWinOpen_) {
    nextInput = getInput();
    if (move(nextInput)) printMenu();
  }
}
void Menu::openMenu() {
  startWin();
  printMenu();
}
void Menu::printMenu() const {
  if (!isWinOpen_) return;
  ::move(0, 0);
  erase();
  clear();
  setColor(TITLE);
  addstr(title);
  unsetColor(TITLE);
  int startPos;
  int cursorPos = 0;
  int titleWidth;
  getyx(stdscr, startPos, titleWidth);
  startPos += 2;
  for (int i = 0; i < (int)optionList.size(); ++i) {
    ::move(startPos + i, 0);
    // TODO: Move if statements into helper-function.
    if (optionList[i]->isHighlighted_) {
      setColor(HIGHLIGHTED);
      addch(' ');
      cursorPos = startPos + i;
    } else if (!optionList[i]->isSelectable_) {
      setColor(DISABLED);
    } else {
      setColor(NORMAL);
    }
    /* if (optionList[i]->isNumber) {
    } else if (optionList[i]->isTextInput) {
      addch('[');
    } else if (optionList[i]->isList) {
      addstr(optionList[i]->text_);
      addstr(": <");
    } */
    addstr(optionList[i]->GetPrefix());
    addstr(optionList[i]->GetText());
    addstr(optionList[i]->GetSuffix());
    /* if (optionList[i]->isNumber) {
      addch('>');
    } else if (optionList[i]->isTextInput) {
      addch(']');
    } else if (optionList[i]->isList) {
      addch('>');
    } */
    if (optionList[i]->isHighlighted_) {
      unsetColor(HIGHLIGHTED);
    } else if (!optionList[i]->isSelectable_) {
      unsetColor(DISABLED);
    } else {
      unsetColor(NORMAL);
    }
  }
  setColor(INSTRUCTIONS);
  ::move(startPos++, 40);
  addstr("Controls:");
  ::move(startPos++, 40);
  addstr("UP:      K or \u2191 (Up arrow)");
  ::move(startPos++, 40);
  addstr("DOWN:    J or \u2193 (Down arrow)");
  ::move(startPos++, 40);
  addstr("LEFT:    H or \u2191 (Left arrow)");
  ::move(startPos++, 40);
  addstr("RIGHT:   L or \u2192 (Right arrow)");
  ::move(startPos++, 40);
  addstr("SELECT:  Enter or HINT or GIVE UP");
  ::move(startPos++, 40);
  addstr("HINT:    \"");
  ::move(startPos++, 40);
  addstr("GIVE UP: ?");
  ::move(startPos++, 40);
  addstr("QUIT:    Q");
  unsetColor(INSTRUCTIONS);
  ::move(cursorPos, 0);
  refresh();
}
void Menu::closeMenu() { endWin(); }
void Menu::startWin() {
  // Handle NCurses.
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  // Colors
  start_color();
  init_pair(HIGHLIGHTED, COLOR_CYAN, COLOR_BLACK);
  init_pair(NORMAL, COLOR_WHITE, COLOR_BLACK);
  init_pair(TITLE, COLOR_CYAN, COLOR_BLACK);
  init_pair(INSTRUCTIONS, COLOR_YELLOW, COLOR_BLACK);
  init_pair(BACKGROUND, COLOR_BLACK, COLOR_BLACK);
  init_pair(ERROR, COLOR_BLACK, COLOR_RED);
  init_pair(DISABLED, COLOR_RED, COLOR_BLACK);

  // TODO: Doesn't seem to work?
  bkgd(COLOR_PAIR(BACKGROUND));

  isWinOpen_ = true;
}
void Menu::endWin() {
  endwin();
  isWinOpen_ = false;
}
Campbell::menu::Input Menu::getInput() const {
  wchar_t input = getch();
  switch (input) {
    case KEY_DOWN:
    case 'J':
    case 'j':
      return DOWN;
    case KEY_UP:
    case 'K':
    case 'k':
      return UP;
    case KEY_LEFT:
    case 'H':
    case 'h':
      return LEFT;
    case KEY_RIGHT:
    case 'L':
    case 'l':
      return RIGHT;
    case 'Q':
    case 'q':
      return QUIT;
    case 10: // Enter
    case KEY_ENTER:
    case '\'':
    case '\"':
    case '/':
    case '?':
      return SELECT;
    default:
      return NONE;
  }
}
bool Menu::move(Input direction) {
  switch (optionList[currentIndex]->input(direction)) {
    case UP:
    case DOWN: {
      int nextIndex = getNextIndex(direction);
      if (nextIndex != currentIndex) {
        optionList[currentIndex]->isHighlighted_ = false;
        currentIndex = nextIndex;
        optionList[currentIndex]->isHighlighted_ = true;
        return true;
      } else {
        return false;
      }
    }
    case SELECT:
      return false;
    case LEFT:
    case RIGHT:
      return false;
    case QUIT:
      closeMenu();
      return true;
    case NONE:
      return false;
    case UNKONWN:
    default:
      setColor(ERROR);
      addstr("An error occurred!");
      unsetColor(ERROR);
      return false;
  }
}
void Menu::AddOption(Option* newOption) {
  optionList.push_back(newOption);
  if (newOption->isHighlighted_) {
    currentIndex = optionList.size() - 1;
  }
}
int Menu::getNextIndex(Input direction) const {
  int multiplier = 1;
  if (direction == UP) multiplier = -1;
  for (int i = currentIndex + multiplier;
       (multiplier > 0) ? i < (int)optionList.size() : i >= 0;
       i += multiplier) {
    if (optionList[i]->isSelectable_) return i;
  }
  return currentIndex;
}
std::string Menu::getString() const {
  std::string input;
  char ch;

  nocbreak();
  echo();

  int y, x;
  getyx(stdscr, y, x);
  ::move(y, x + 2);

  setColor(HIGHLIGHTED);
  while ((ch = getch())) {
    if (ch == '\n' || ch <= 31) break;
    unsetColor(HIGHLIGHTED);
    input.push_back(ch);
    printMenu();
    getyx(stdscr, y, x);
    ::move(y, x + 2);
    setColor(HIGHLIGHTED);
  }
  unsetColor(HIGHLIGHTED);

  cbreak();
  noecho();

  return input;
}
void Menu::setColor(Colors index) const {
  if (!has_colors()) return;
  attron(COLOR_PAIR(index));
}
void Menu::unsetColor(Colors index) const {
  if (!has_colors()) return;
  attroff(COLOR_PAIR(index));
}
}  // namespace menu
}  // namespace Campbell
