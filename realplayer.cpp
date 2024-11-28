#include "realplayer.h"
#include <iostream>
using namespace std;

void display_player_hand(Card * player_hand, int &player_hand_count) {
  if (player_hand_count == 0) {
    cout << "You have no card in your hand." << endl;
  }else {
    cout <<
}
void handle_player_input(Card * player_hand, int &player_hand_count) {
  string command;
  cout << "Now it's your turn." << endl; 
  if (player_hand_count == 0) {
    cout << "You have no card in your hand. Your turn will be skipped." << endl;
    return;
  }else {
    cout << "You can choose:" << endl;
    cout << "1. Play cards." << "\n" << "2. Skip this turn." << "\n" << "Quit Game." << "\n" << endl;
    cout << "Please enter your choice: " << "\n" << "(enter corresponding number: 1, 2, or 'Quit')" << endl;
    cin >> command;

    while (command != "1" && command != "2" && command != "quit" && command != "Quit") {
      cout << "Invalid choice. Please enter 1, 2, or quit: ";
      cin >> command;
    }

    if (command == "quit" || command == "Quit") {
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
        exit(0);
      } else {
        cout << "You chose not to quit the game." << endl;
        cout << "Now it's your turn, you can choose:" << endl;
        cout << "1. Play cards." << "\n" << "2. Skip this turn." << "\n" << "Quit Game" << endl;
        cout << "Please enter your choice: " << "\n" << "(enter corresponding number: 1, 2, or 'Quit')" << endl;
        cin >> command;
        while (command != "1" && command != "2" && command != "quit" && command != "Quit") {
          cout << "Invalid choice. Please enter 1, 2, or quit: ";
          cin >> command;
        }
      }
    }
    if (command == "1") {
      
    
    }else if (command == "2") {
      cout << "You have skipped your turn." << endl;
    }
  }
}
