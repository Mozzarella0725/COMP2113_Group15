#include "game.h"
#include "rule.h"
#include "card.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

extern int challenger_id;    
extern int current_player_id;

void handle_player_input(Player& player, Player& previous_player) {
    string command;

    if (player.hand_count == 0) {
        cout << "You have no cards in your hand. Your turn will be skipped." << endl;
        return;
    }

    // Display player's hand
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

    // Present options to the player
    cout << "Options:\n1. Play cards\n2. Challenge the previous player\n3. Quit game" << endl;
    cout << "Enter your choice (1, 2, or 3): ";
    cin >> command;

    // Validate menu input
    while (command != "1" && command != "2" && command != "3") {
        cout << "Invalid choice. Please enter 1, 2, or 3: ";
        cin >> command;
    }

    // Handle quitting
    if (command == "3") {
        cout << "Are you sure you want to quit the game? (Enter 'yes' to quit): ";
        string confirm;
        cin >> confirm;
        if (confirm == "Yes" || confirm == "yes") {
            cout << "You have chosen to quit. Thanks for playing!" << endl;
            exit(0);
        }
        return;
    }

    // Handle challenge
    if (command == "2") {
        cout << player.name << " is challenging " << previous_player.name << "!" << endl;
        challenger_id = player.id;
        handle_challenge(&player, &previous_player);
        return;
    }

    // Handle playing cards
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

        // Select cards to play
        cout << "Enter number to select the cards to play (1 - " << player.hand_count << "):" << endl;
        int selected[3] = {-1, -1, -1};
        for (int i = 0; i < num; ++i) {
            int card_index;
            cin >> card_index;
            while (card_index < 1 || card_index > player.hand_count) {
                cout << "Invalid card selection. Choose again: ";
                cin >> card_index;
            }
            selected[i] = card_index - 1;
        }

        // Store played cards
        player.num_played_cards = num;
        for (int i = 0; i < num; ++i) {
            player.played_cards[i] = player.hand[selected[i]];
        }

        // Remove played cards from hand
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
