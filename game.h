#ifndef GAME_H
#define GAME_H

#include "card.h"
#include <stdbool.h> // newly added, for cheat

// Player structure: each player has their hand, score, etc.
typedef struct {
    Card hand[5];      // Player's hand of cards
    Card played_cards[5];// Cards played during the turn
    int num_played_cards;// Number of cards played duiring the turn
    int hand_count;    // Number of cards in the player's hand
    int id;            // Unique ID for the player
    int death_chamber;       // Remaining bullets (1 bullet per player)
    bool is_eliminated;// Flag to indicate if the player is eliminated
    char name[50];     // Name of the player
} Player;

// Main game logic function declarations
void start_game();
void handle_turn(Player* player, Deck* deck);
void handle_challenge(Player* challenger, Player* previous_player);

//newly added, for cheat
void show_other_players_cards(Player* players, int num_players, int current_player);
void process_player_input(Player* player, int num_players, int current_player);

#endif
