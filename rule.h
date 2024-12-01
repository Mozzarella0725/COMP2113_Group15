#ifndef RULE_H
#define RULE_H

#include <stdbool.h> // For 'bool' type
#include "/include/game.h"  // Include Player structure
#include "/include/card.h"    // Include Card structure

/**
 * Checks if the cards played by the player match their declaration.
 * 
 * played_cards: Array of cards played by the current player.
 * num_cards: Number of cards played in the current turn.
 * called_value: The declared card value for this round.
 * 
 * Return True if the player is honest. Return False if the player is bluffing.
 */
bool check_bluff(Card* played_cards, int num_cards, int called_value);

/**
 * Handles the result of a bluff challenge.
 * 
 * challenger Pointer to the Player who initiated the challenge.
 * current_player Pointer to the Player whose play is being challenged.
 */
void handle_challenge(Player* challenger, Player* current_player);

void display_pistol();

/**
 * Executes the death roulette for a player.
 * 
 * player Pointer to the Player undergoing the death roulette.
 */
void trigger_death_roulette(Player* player);

#endif
