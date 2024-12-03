#include "game.h"
#include "rule.h"
#include "card.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

extern int challenger_id;    
extern int current_player_id;

void handle_player_input(Player& player, Player previous_player) {
    string command;

    if (player.hand_count == 0) {
        cout << "You have no cards in your hand. Your turn will be skipped." << endl;
        return;
    }

    cout << "Your hand:" << endl;
    for (int i = 0; i < player.hand_count; ++i) {
        if (player.hand[i].value == 1) {
              cout << "Card " << i + 1 << ": [Ace]" << endl;
        } else if (player.hand[i].value == 2) {
              cout << "Card " << i + 1 << ": [King]" << endl;
        } else if (player.hand[i].value == 3) {
              cout << "Card " << i + 1 << ": [Queen]" << endl;
        } else if (player.hand[i].value == 0) {
              cout << "Card " << i + 1 << ": [Joker]" << endl;
        }
    }

    if (previous_player.num_played_cards == 0) {
	    cout << "Options:\n1. Play cards\nQuit Game" << endl;
   	    cout << "Enter your choice (1 or 'quit'): ";
   	    cin >> command;
    }else {
    	cout << "Options:\n1. Play cards\n2. Challenge the previous player\n3. Quit Game" << endl;
    	cout << "Enter your choice (1, 2, or 'quit'): ";
    	cin >> command;
    }

    while (previous_player.num_played_cards == 0 && command != "1" && command != "quit" || previous_player.num_played_cards != 0 && command != "1" && command != "2" && command != "quit") {
        cout << "Invalid choice. Please enter again: ";
        cin >> command;
    }

    if (command == "quit") {
        cout << "Are you sure you want to quit the game? (Enter 'yes' to quit): ";
        string confirm;
        cin >> confirm;
        if (confirm == "Yes" || confirm == "yes") {
            cout << "You have chosen to quit. Thanks for playing!" << endl;
            exit(0);
        }
        return;
    }

    if (command == "2") {
        cout << player.name << " is challenging " << previous_player.name << "!" << endl;
        challenger_id = player.id;
        handle_challenge(&player, &previous_player);
        return;
    }

    if (command == "1") {
        int num;
        cout << "How many cards do you want to play? (1 - " << min(player.hand_count, 3) << "): ";
        while (true) {
            cin >> num;
            if (num < 1 || num > min(player.hand_count, 3)) {
                cout << "Invalid input. Enter a number between 1 and " << min(player.hand_count, 3) << ": ";
            } else {
                break;
            }
        }

        cout << "Enter number to select the cards to play (1 - " << player.hand_count << "):" << endl;
        vector<int> selected;
        while (selected.size() < num) {
	    int card_index;
            cin >> card_index;
	    while (card_index < 1 || card_index > player.hand_count) {
                cout << "Invalid card selection. Choose again: ";
                cin >> card_index;
            }
	    card_index -= 1;
	    if (find(selected.begin(), selected.end(), card_index) != selected.end()) {
        	cout << "Card already selected. Choose another: ";
            } else {
        	selected.push_back(card_index);
            }
	    }

        player.num_played_cards = num;
        for (int i = 0; i < num; ++i) {
            player.played_cards[i] = player.hand[selected[i]];
        }

        for (int i = num - 1; i >= 0; --i) {
            int idx = selected[i];
            for (int j = idx; j < player.hand_count - 1; ++j) {
                player.hand[j] = player.hand[j + 1];
            }
            player.hand_count--;
        }

        cout << "You played " << num << " card(s): ";
        for (int i = 0; i < num; ++i) {
            if (player.played_cards[i].value == 1) {
                  cout << "Card " << i + 1 << ": [Ace]" << endl;
            } else if (player.played_cards[i].value == 2) {
                  cout << "Card " << i + 1 << ": [King]" << endl;
            } else if (player.played_cards[i].value == 3) {
                  cout << "Card " << i + 1 << ": [Queen]" << endl;
            } else if (player.played_cards[i].value == 0) {
                  cout << "Card " << i + 1 << ": [Joker]" << endl;
            }
        }
        cout << endl;
    }
}
