#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "card.h"

// Start the game: initialize deck and players
void start_game() {
    Deck deck;
    generate_deck(&deck);   // Generate the deck
    shuffle_deck(&deck);    // Shuffle the deck

    // Initialize players
    Player player1 = {{}, 5, 0, 1, 1};  // Player 1 with 5 cards and 1 bullet
    deal_cards(&deck, player1.hand, 5);  // Deal 5 cards to player 1
    print_deck(&deck);   // Print the deck for debugging

    // Handle the player's turn
    handle_turn(&player1, &deck);
}

// Handle a player's turn: play cards, choose to challenge, etc.
void handle_turn(Player* player, Deck* deck) {
    printf("Player %d's turn\n", player->id);
    printf("Hand: ");
    for (int i = 0; i < player->hand_count; i++) {
        printf("%d%c ", player->hand[i].value, player->hand[i].suit);
    }
    printf("\n");

    // Ask the player to select how many cards to play (1-3 cards)
    printf("How many cards do you want to play? ");
    int num_cards;
    scanf("%d", &num_cards);

    // Check if the player has enough cards to play
    if (num_cards <= player->hand_count) {
        printf("You chose to play %d cards.\n", num_cards);
        player->hand_count -= num_cards;  // Decrease the player's hand count
    } else {
        printf("Not enough cards to play!\n");
    }

    // Ask if the player wants to challenge the previous player's statement
    char challenge;
    printf("Do you want to challenge the previous player's statement? (y/n): ");
    scanf(" %c", &challenge);
    
    if (challenge == 'y' || challenge == 'Y') {
        handle_challenge(player, NULL);  // Currently, NULL is used for the previous player
    }
}

// Handle the challenge: verify if the previous player was lying
void handle_challenge(Player* challenger, Player* previous_player) {
    // Here you can add logic for verifying the played cards
    printf("Challenge in progress...\n");

    // For now, assume the challenge fails, and we proceed to the death roulette
    printf("Challenge failed. Proceeding to death roulette!\n");
    int result = rand() % 6;  // Randomly simulate the death roulette
    if (result == 0) {
        printf("You are eliminated!\n");
    } else {
        printf("Lucky! You escaped!\n");
    }
}
