#include "realplayer.h"
#include <iostream>
#include <string>
using namespace std;

void display_player_hand(Card * player_hand, int player_hand_count) {
  if (player_hand_count == 0) {
    cout << "You have no card in your hand." << endl;
  }else {
    for (int i = 0; i < player_hand_count; ++i) {
      if (player_hand[i].value == 1) {
        cout << "Card" << i + 1 << ":" << "\n" << "「Ace」" << endl;
        cout << endl;
      }else if (player_hand[i].value == 2) {
        cout << "Card" << i + 1 << ":" << "\n" << "「King」" << endl;
        cout << endl;
      }else if (player_hand[i].value == 3) {
        cout << "Card" << i + 1 << ":" << "\n" << "「Queen」" << endl;
        cout << endl;
      }else if (player_hand[i].value == 0) {
          cout << "Card" << i + 1 << ":" << "\n" << "「Joker」" << endl;
          cout << endl;
      }
    }
  }
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
      
      int num;
      
      if (player_hand_count >= 3) {
        cout << "How many cards do you want to play in this round (minimum 1, maximum 3)." << endl;
        cin >> num;
        while (num > 3 || num < 1) {
          cout << "Invalid number. Please enter again." << endl;
          cin >> num;
        }
      }else {
        cout << "How many cards do you want to play in this round (minimum 1, maximum " << player_hand_count << ")." << endl;
        cin >> num;
        while (num > player_hand_count || num < 1) {
          cout << "Invalid number. Please enter again." << endl;
          cin >> num;
        }
      }

      cout << "which card(s) you want to play? (1 - " << player_hand_count << ")"<< endl;
      cout << "Press enter after each number." << "(Think carefully! You cannot undo the selection.)" << endl;
      int selected[3] = {-1, -1, -1};
      for (int i = 0; i < num; ++i) {
        int Num;
        cin >> Num;
        while (Num < 1 || Num > player_hand_count || find(begin(selected), end(selected), card_index) != end(selected)) {
          cout << "Invalid number. Please enter again." << endl;
          cin << Num;
        }
        selected[i] = Num;
      }

      cout << "You have chosen these cards to play." << endl;
      for (int i = 0; i < num; ++i) {
        while (selected[i] != -1) {
          if (player_hand[selected[i]].value == 1) {
            cout << "Card" << i + 1 << ":" << "\n" << "「Ace」" << endl;
            cout << endl;
          }else if (player_hand[selected[i]].value == 2) {
            cout << "Card" << i + 1 << ":" << "\n" << "「King」" << endl;
            cout << endl;
          }else if (player_hand[selected[i]].value == 3) {
            cout << "Card" << i + 1 << ":" << "\n" << "「Queen」" << endl;
            cout << endl;
          }else if (player_hand[selected[i]].value == 0) {
              cout << "Card" << i + 1 << ":" << "\n" << "「Joker」" << endl;
              cout << endl;
          }
        }
      }

      for (int i = num - 1; i >= 0; --i) {
        int idx = selected[i];
        for (int j = idx; j < player_hand_count - 1; ++j) {
            player_hand[j] = player_hand[j + 1];
        }
      player_hand_count--;
      }
      cout << "You played the selected cards." << endl;
          
    }else if (command == "2") {
      cout << "You have skipped your turn." << endl;
    }
  }
}
