#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/card.h"

// Generate the deck
void generate_deck(Deck* deck, int num_decks) {
    char suits[] = {'H', 'S', 'C', 'D'};
    int index = 0;

    for (int d = 0; d < num_decks; d++) {  // Support multiple decks
        for (int i = 1; i <= 13; i++) {
            for (int j = 0; j < 4; j++) {
                deck->deck[index].value = i;
                deck->deck[index].suit = suits[j];
                index++;
            }
        }
    }
    deck->size = index; // Calculate the total number of cards
    deck->top = 0;      // Initialize the top pointer
}

// Shuffle the deck
void shuffle_deck(Deck* deck) {
    srand(time(NULL));  // Random seed
    for (int i = deck->size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck->deck[i];
        deck->deck[i] = deck->deck[j];
        deck->deck[j] = temp;
    }
}

// Deal cards to players
void deal_cards(Deck* deck, Card* hand, int num_cards) {
    for (int i = 0; i < num_cards; i++) {
        if (deck->top < deck->size) {
            hand[i] = deck->deck[deck->top++];
        } else {
            printf("Deck is empty! Cannot deal more cards.\n");
        }
    }
}

// Print the deck (for debugging)
void print_deck(Deck* deck) {
    for (int i = 0; i < deck->size; i++) {
        printf("%d%c ", deck->deck[i].value, deck->deck[i].suit);
    }
    printf("\n");
}
