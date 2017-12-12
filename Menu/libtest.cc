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

// TODO: Test disabling isHighlightable.
// TODO: Test each feature in each option.
int main() {
  // Test adding an option works.
  std::cout << "Adding Button: ";
  mainMenu.AddOption(new Campbell::menu::Button(
      mainMenu, "Hello world!", &MainMenuCallbacks::quitCallback, true, true));
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)1);

  // Tests that menu can open with basic settings.
  std::cout << "Opening menu (No result is pass) " << std::endl;
  mainMenu.openMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), true);

  // Ensure menu closes propelry.
  std::cout << "Closing menu: ";
  mainMenu.closeMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), false);

  // Add multiple options and ensure the vector grows appropriately.
  std::cout << "Adding Buttons: ";
  mainMenu.AddOption(new Campbell::menu::Button(mainMenu, "Second Button",
                                                &MainMenuCallbacks::nothing));
  mainMenu.AddOption(new Campbell::menu::Button(mainMenu, "Third Button",
                                                   &MainMenuCallbacks::error));
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)3);

  std::cout << "Checking current index: ";
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 0);

  // Ensures menu can still open with additional options.
  std::cout << "Opening menu (No result is pass) " << std::endl;
  mainMenu.openMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), true);

  // Add button while menu is open and move current position to the new option.
  mainMenu.AddOption(new Campbell::menu::Button(
      mainMenu, "Fourth Button", &MainMenuCallbacks::nothing, true, true));

  std::cout << "Closing menu: ";
  mainMenu.closeMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), false);

  // Ensure previously added option was added properly and moved current index.
  std::cout << "Added Buttons: ";
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)4);

  std::cout << "Checking current index: ";
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 3);

  // Check basic movement within menu.
  std::cout << "Moving up: ";
  mainMenu.move(Campbell::menu::UP);
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 2);

  // Move past limit and ensure the limit is not passed.
  std::cout << "Moving down: ";
  for (int i = 0; i < 10; ++i) {
    mainMenu.move(Campbell::menu::DOWN);
  }
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 3);

  // Move past limit and ensure the limit is not passed.
  std::cout << "Moving farther up: ";
  for (int i = 0; i < 10; ++i) {
    mainMenu.move(Campbell::menu::UP);
  }
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 0);

  std::cout << "Opening menu (No result is pass) " << std::endl;
  mainMenu.openMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), true);

  // Test that choosing quit will close menu.
  std::cout << "Selecting quit: ";
  mainMenu.move(Campbell::menu::SELECT);
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), false);

  // Ensure clearing options works.
  std::cout << "Clearing Options: ";
  mainMenu.clearOptions();
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)0);

  std::cout << "Opening menu (No result is pass) " << std::endl;
  mainMenu.openMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), true);

  // Check basic movement within without any options available.
  std::cout << "Moving up: ";
  mainMenu.move(Campbell::menu::UP);
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 0);
  std::cout << "Moving down: ";
  mainMenu.move(Campbell::menu::DOWN);
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 0);

  std::cout << "Closing menu: ";
  mainMenu.closeMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), false);

  // Test each individual option

  // BUTTON
  std::cout << "Adding Button: ";
  mainMenu.AddOption(new Campbell::menu::Button(mainMenu, "Fifth button",
                                                &MainMenuCallbacks::nothing));
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)1);
  std::cout << "Checking current index ";
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 0);

  // INTEGER
  std::cout << "Adding Integer: ";
  mainMenu.AddOption(
      new Campbell::menu::Integer(mainMenu, 2, &MainMenuCallbacks::nothing));
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)2);
  std::cout << "Checking current index ";
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 0);

  // LIST
  std::cout << "Adding List: ";
  std::vector<std::string> listOptions(0);
  listOptions.push_back("Hello");
  listOptions.push_back("World");
  listOptions.push_back("This");
  listOptions.push_back("Is");
  listOptions.push_back("Fun");
  mainMenu.AddOption(
      new Campbell::menu::List(mainMenu, "LIST OPTION", listOptions));
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)3);
  std::cout << "Checking current index ";
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 0);

  // TEXTINPUT
  std::cout << "Adding TextInput: ";
  mainMenu.AddOption(new Campbell::menu::TextInput(mainMenu, "TextInnput"));
  Campbell::Test::ASSERT(mainMenu.getOptionList().size(), (size_t)4);
  std::cout << "Checking current index ";
  Campbell::Test::ASSERT(mainMenu.getCurrentIndex(), 0);

  // Ensure menu can be opened with each option.
  std::cout << "Opening menu (No result is pass) " << std::endl;
  mainMenu.openMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), true);

  std::cout << "Closing menu: ";
  mainMenu.closeMenu();
  Campbell::Test::ASSERT(mainMenu.isWinOpen(), false);

  return 0;
}
