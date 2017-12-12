#include <curses.h>
#include <iostream>
#include <vector>
#include "../CampbellLib.h"
#include "Button.h"
#include "Integer.h"
#include "List.h"
#include "Menu.h"
#include "TextInput.h"

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

  std::cout << "Adding Integer: ";
  mainMenu.AddOption(new Campbell::menu::Integer(
      mainMenu, 2, &MainMenuCallbacks::nothing, true, true));
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)2);
  std::cout << "Checking current index ";
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 1);

  std::cout << "Adding List: ";
  std::vector<std::string> listOptions(0);
  listOptions.push_back("Hello");
  listOptions.push_back("World");
  listOptions.push_back("This");
  listOptions.push_back("Is");
  listOptions.push_back("Fun");
  mainMenu.AddOption(new Campbell::menu::List(mainMenu, "LIST OPTION",
                                              listOptions, true, true));
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)3);
  std::cout << "Checking current index ";
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 2);

  std::cout << "Adding TextInput: ";
  mainMenu.AddOption(
      new Campbell::menu::TextInput(mainMenu, "TextInnput", true, true));
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)4);
  std::cout << "Checking current index ";
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 3);

  std::cout << "Opening menu (No result is pass) " << std::endl;
  mainMenu.openMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), true);

  std::cout << "Closing menu: ";
  mainMenu.closeMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), false);

  return 0;
}
