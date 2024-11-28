#include realplayer.h
#include <iostream>
using namespace std;

int main() {
  int command;
  cout << "Now it's your turn, you can choose:" << endl;
  cout << "1. Play cards." << "\n" << "2. Skip this turn." << endl;
  cout << "Please enter your choice: " << "\n" << "(enter corresponding number: 1 or 2)" << endl;
  cin >> command;
  while (command != 2) {
      handle_player_input();
    }
    cout << "Enter your next choice: " << endl;
    cin >> command;
  }
  cout << "You have skipped your turn." << endl;
  return 0;
}
