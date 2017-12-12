#include <curses.h>
#include <iostream>
#include <vector>
#include "../CampbellLib.h"
#include "Button.h"
#include "Menu.h"

struct MainMenuCallbacks : public Campbell::Callbacks {
  int quitCallback() { return 100; }
};
MainMenuCallbacks* callbacks = new MainMenuCallbacks;
Campbell::menu::Menu mainMenu(callbacks);

int main() {
  std::cout << "Adding Button: ";
  mainMenu.AddOption(new Campbell::menu::Button(
      mainMenu, "Hello world!", &MainMenuCallbacks::quitCallback, true, true));
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)1);

  std::cout << "Opening menu (No result is pass) " << std::endl;
  mainMenu.openMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), true);

  std::cout << "Closing menu: ";
  mainMenu.closeMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), false);

  std::cout << "Adding Buttons: ";
  mainMenu.AddOption(new Campbell::menu::Button(mainMenu, "Second Button",
                                                &MainMenuCallbacks::nothing));
  mainMenu.AddOption(new Campbell::menu::Button(mainMenu, "Third Button",
                                                   &MainMenuCallbacks::error));
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)3);

  std::cout << "Checking current index: ";
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 0);

  std::cout << "Opening menu (No result is pass) " << std::endl;
  mainMenu.openMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), true);

  mainMenu.AddOption(new Campbell::menu::Button(
      mainMenu, "Fourth Button", &MainMenuCallbacks::nothing, true, true));

  std::cout << "Closing menu: ";
  mainMenu.closeMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), false);

  std::cout << "Added Buttons: ";
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)4);

  std::cout << "Checking current index: ";
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 3);

  std::cout << "Moving up: ";
  mainMenu.move(Campbell::menu::UP);
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 2);

  std::cout << "Moving down: ";
  for (int i = 0; i < 10; ++i) {
    mainMenu.move(Campbell::menu::DOWN);
  }
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 3);

  std::cout << "Moving farther up: ";
  for (int i = 0; i < 10; ++i) {
    mainMenu.move(Campbell::menu::UP);
  }
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 0);

  std::cout << "Opening menu (No result is pass) " << std::endl;
  mainMenu.openMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), true);

  std::cout << "Selecting quit: ";
  mainMenu.move(Campbell::menu::SELECT);
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), false);

  std::cout << "Clearing Options: ";
  mainMenu.clearOptions();
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)0);

  std::cout << "Adding Button: ";
  mainMenu.AddOption(new Campbell::menu::Button(
      mainMenu, "Fifth button", &MainMenuCallbacks::nothing, true, true));
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)1);
  std::cout << "Checking current index ";
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 0);

  return 0;
}
