#ifndef GAME_H
#define GAME_H

#include "card.h"

// Player structure: each player has their hand, score, etc.
typedef struct {
    Card hand[5];      // Player's hand of cards
    int hand_count;    // Number of cards in the player's hand
    int score;         // Player's score
    int id;            // Unique ID for the player
    int bullets;       // Remaining bullets (1 bullet per player)
} Player;

// Main game logic function declarations
void start_game(SDL_Renderer* renderer, SDL_Texture* card_back, SDL_Texture* card_front);
void handle_turn(Player* player, Deck* deck);
void handle_challenge(Player* challenger, Player* previous_player);


#endif
