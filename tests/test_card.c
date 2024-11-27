#include <assert.h>
#include "../include/card.h"

// Test generate_deck function
void test_generate_deck() {
    Deck deck;
    generate_deck(&deck, 1);  // Create one deck
    assert(deck.size == 52);  // Check if there are 52 cards
    assert(deck.deck[0].value == 1); // Check if the first card is Ace of Hearts
    assert(deck.deck[51].value == 13); // Check if the last card is King of Diamonds
    printf("Generate deck test passed!\n");
}

// Test shuffle_deck function
void test_shuffle_deck() {
    Deck deck;
    generate_deck(&deck, 1);
    shuffle_deck(&deck);  // Shuffle the deck
    assert(deck.top == 0);  // Ensure the top pointer is still valid after shuffle
    printf("Shuffle deck test passed!\n");
}

// Test deal_cards function
void test_deal_cards() {
    Deck deck;
    generate_deck(&deck, 1);
    Card hand[5];
    deal_cards(&deck, hand, 5);
    assert(deck.top == 5);  // Check the deck's state after dealing cards
    assert(hand[0].value != 0);  // Ensure the hand has valid cards
    printf("Deal cards test passed!\n");
}

// Main function to run the tests
int main() {
    test_generate_deck();
    test_shuffle_deck();
    test_deal_cards();
    printf("All tests passed!\n");
    return 0;
}
