#include realplayer.h
#include action_key.h
#include <iostream>
#include <string>
using namespace std;

int main() {
  string command;
  cout << "Now it's your turn, you can choose:" << endl;
  cout << "1. Play cards." << "\n" << "2. Skip this turn." << "\n" << "Quit Game" << endl;
  cout << "Please enter your choice: " << "\n" << "(enter corresponding number: 1, 2, or quit)" << endl;
  cin >> command;
  if (command == "1") {
    display_player_hand();
    handle_player_input();
  }else if (command == "2") {
    cout << "You have skipped your turn." << endl;
  }else if (command == "quit") {
    quit_game();
  }else {
    cout << "Invalid choice. Please enter 1, 2, or quit" << endl;
  }
  return 0;
}
