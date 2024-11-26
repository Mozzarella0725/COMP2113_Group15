#ifndef PLAYER_H
#define PLAYER_H

#include "card.h" // Include the Card struct definition

#define MAX_CARDS 5 // Maximum number of cards a player can hold

struct Player {
    int id;                        // Unique identifier for the player
    struct Card hand[MAX_CARDS];   // Cards currently held by the player
    struct Card played_cards[MAX_CARDS]; // Cards played during the turn
    int num_played_cards;          // Number of cards played during the turn
    bool is_eliminated;            // Flag to indicate if the player is eliminated
    int death_chamber;             // Chamber number in the death roulette
};

#endif
