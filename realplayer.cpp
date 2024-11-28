#include "realplayer.h"
#include <iostream>
using namespace std;

void display_player_hand() {

void handle_player_input() {

bool quit_game() {
  string check;
  cout << "Are you sure you want to quit the game?" << endl;
  cout << "After quitting the game, the records of this game will be cleared." << endl;
  cout << "Please enter 'Yes' or 'No': ";
  cin >> check;

  while (check != "Yes" && check != "No" && check != "yes" && check != "no") {
    cout << "Invalid choice. Please enter 'Yes' or 'No': ";
    cin >> check;
  }

  if (check == "Yes" || check == "yes") {
    cout << "You have chosen to quit this game!" << endl;
    cout << "Thanks for playing!" << endl;
    return true;
  } else {
    cout << "You chose not to quit the game." << endl;
    return false;
  }
}
