#include <iostream>
#include <vector>
#include "Menu.h"
#include "Button.h"
#include "../CampbellLib.h"

class QuitCallback : public Campbell::Callbacks {
  int callback_() { return 100; }
};
QuitCallback quitCallback;

int main() {
  Campbell::Menu mainMenu;
  Campbell::Button first(mainMenu, "Hello world!", quitCallback, true, true);

  mainMenu.addOption(first);
  return 0;
}
