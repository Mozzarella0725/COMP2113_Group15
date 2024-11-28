#include realplayer.h
#include <iostream>
using namespace std;

int main() {
  int command;
  cout << "Now it's your turn, you can choose:" << endl;
  cout << "1. Display your card." << "\n" << "2. Play cards." << "\n" << "3. Skip this turn." << endl;
  cout << "Please enter your choice: " << "\n" << "(enter corresponding number: 1, 2, or 3.)" << endl;
  cin >> command;
  while (command != 3) {
    if (command == 1) {
      display_player_hand();
    }else {
      handle_player_input();
    }
    cout << "Enter your next choice: " << endl;
    cin >> command;
  }
  cout << "You have skipped your turn." << endl;
  return 0;
}
