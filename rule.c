#include "rule.h"
#include <stdio.h>
#include <stdlib.h> // For rand()

// Global variables

// Declared target card value. Should be updated each round.
int called_value = 0;       

// Flag indicating a bluff. Regarded as false until proven otherwise.
bool is_bluff = false;      

// Challenger's player ID
int challenger_id = -1;     

// Current player's ID
int current_player_id = -1; 

/**
 * Checks if the cards played by the player match their declaration.
 * 
 * played_cards: Array of cards played by the current player.
 * num_cards: Number of cards played in the current turn.
 * called_value: The declared card value for this round.
 * 
 * Return True if the player is honest. Return False if the player is bluffing.
 */
bool check_bluff(Card* played_cards, int num_cards, int called_value) {
    for (int i = 0; i < num_cards; i++) {
        
        // If a card doesn't match the declared value and isn't a Joker, it's a bluff
        if (played_cards[i].value != called_value && !played_cards[i].is_joker) {
            return false;
        }
    }
    
    return true; // All cards match the declared value or are Jokers
}

/**
 * Handles the result of a bluff challenge.
 * 
 * challenger Pointer to the Player who initiated the challenge.
 * current_player Pointer to the Player whose play is being challenged.
 */
void handle_challenge(Player* challenger, Player* current_player) {
    
    is_bluff = check_bluff(current_player->played_cards, current_player->num_played_cards, called_value);

    if (!is_bluff) {
        
        // Player was truthful
        printf("Challenge failed! Player %d was truthful.\n", current_player->id);
        trigger_death_roulette(challenger);
    } else {
        
        // Player was bluffing
        printf("Challenge successful! Player %d was bluffing.\n", current_player->id);
        trigger_death_roulette(current_player);
    }
}

/**
 * Executes the death roulette for a player.
 * 
 * player Pointer to the Player undergoing the death roulette.
 */
void trigger_death_roulette(Player* player) {
    
    player->death_chamber++; // Increment death count for this player

    // Reduce chambers based on death count
    int chambers = 6 - player->death_chamber + 1;           
    // Randomly pick a chamber
    int chamber = rand() % chambers;           

    if (chamber == 0) { 
        
        // If it's the first chamber or guaranteed death
        printf("Player %s fired a live round! They are eliminated.\n", player->name);
        player->is_eliminated = true;
    } else {
        printf("Player %s survived the death roulette. Probability of death increases next time.\n", player->name);
    }
}