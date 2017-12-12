[![Build Status](https://travis-ci.org/CampbellCrowley/CampbellLib.svg?branch=master)](https://travis-ci.org/CampbellCrowley/CampbellLib)

# CampbellLib
Small library of stuff I use often.

## Menu
Contains ncurses based menu system with multiple different option types.

An option can be added to a Menu by using the Menu.addOption(const Option&).  
Provided Options:
- Button
  - Selecting calls the callback.
- Integer
  - Selects integer value. Changing the value calls callback.
- List
  - Has a list of options that the user can choose from.
- TextInput
  - Collects user-typed input.
