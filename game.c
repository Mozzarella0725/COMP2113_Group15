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

    // CHEATcode
    char input[100];
    printf("Enter command (or press Enter to continue): ");
    getchar(); // Clear any leftover newline
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove trailing newline
    
    // CHEAT code check
    if (strcmp(input, "hku is brilliant") == 0) {
        show_other_players_cards(player, 4, player->id - 1); // 4 players total
    }

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

// CHEAT, show cards
void show_other_players_cards(Player* players, int num_players, int current_player) {
    printf("\n=== Other Players' Cards ===\n");
    for (int i = 0; i < num_players; i++) {
        if (i != current_player && !players[i].is_eliminated) {
            printf("Player %d's cards: ", players[i].id);
            for (int j = 0; j < players[i].hand_count; j++) {
                switch(players[i].hand[j].value) {
                    case 1: printf("Ace "); break;
                    case 2: printf("King "); break;
                    case 3: printf("Queen "); break;
                    case 0: printf("Joker "); break;
                    default: printf("%d ", players[i].hand[j].value);
                }
            }
            printf("\n");
        }
    }
    printf("========================\n");
}
