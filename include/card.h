#ifndef CARD_H
#define CARD_H

// Card structure: represents a card, including its value and suit
typedef struct {
    int value;      // Card value (1-13, corresponding to Aces, Kings, Queens)
    char suit;      // Card suit (H: Hearts, S: Spades, C: Clubs, D: Diamonds)
} Card;

// Deck structure: represents the entire deck of cards
typedef struct {
    Card deck[20];  // Deck of a maximum of 20 cards
    int size;       // Current size of the deck
    int top;        // Index pointing to the top of the deck
} Deck;

// Function declarations for card management
void generate_deck(Deck* deck);
void shuffle_deck(Deck* deck);
void deal_cards(Deck* deck, Card* hand, int num_cards);
void print_deck(Deck* deck);

#endif
