#ifndef CARD_H
#define CARD_H

// Card structure: represents a card, including its value and suit
struct Card {
    int value;      // Value of the card: 1 for Ace, 2 for King, 3 for Queen, 0 for Joker
    bool is_joker;  // Flag to indicate if the card is a Joker
};

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
