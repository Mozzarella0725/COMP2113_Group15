#ifndef CARD_H
#define CARD_H

#include <stdbool.h> // For 'bool' type

struct Card {
    int value;      // Value of the card: 1 for Ace, 2 for King, 3 for Queen, 0 for Joker
    bool is_joker;  // Flag to indicate if the card is a Joker
};

#endif
