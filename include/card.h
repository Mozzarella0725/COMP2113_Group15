#ifndef CARD_H
#define CARD_H

// Card structure
typedef struct {
    int value;      // Card value (1-13)
    char suit;      // Card suit (H: Hearts, S: Spades, C: Clubs, D: Diamonds)
} Card;

// Deck structure
typedef struct {
    Card deck[104]; // Support up to two decks
    int size;       // Total size of the deck
    int top;        // Index for the top of the deck
} Deck;

// Function declarations
void generate_deck(Deck* deck, int num_decks);
void shuffle_deck(Deck* deck);
void deal_cards(Deck* deck, Card* hand, int num_cards);
void print_deck(Deck* deck);

#endif
