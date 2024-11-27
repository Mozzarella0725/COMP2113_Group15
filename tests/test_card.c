#include <assert.h>
#include "../include/card.h"

// Test generate_deck function
void test_generate_deck() {
    Deck deck;
    generate_deck(&deck);  // Generate the deck

    // Check if the deck has 20 cards
    assert(deck.size == 20);  

    // Ensure the first card is an Ace of Hearts
    assert(deck.deck[0].value == 1);
    assert(deck.deck[0].suit == 'H');  // 'H' represents Hearts

    // Ensure the last card is a Joker
    assert(deck.deck[deck.size - 1].value == 0);  // Jokers have value 0
    assert(deck.deck[deck.size - 1].suit == 'J');  // Jokers are marked with 'J'

    printf("Generate deck test passed!\n");
}

// Test shuffle_deck function
void test_shuffle_deck() {
    Deck deck;
    generate_deck(&deck);
    shuffle_deck(&deck);  // Shuffle the deck

    // Check if the deck top pointer is still valid after shuffle
    assert(deck.top == 0);  

    // Print shuffled deck for debugging purposes (optional)
    // print_deck(&deck);

    printf("Shuffle deck test passed!\n");
}

// Test deal_cards function
void test_deal_cards() {
    Deck deck;
    generate_deck(&deck);
    Card hand[5];

    // Deal 5 cards to the hand
    deal_cards(&deck, hand, 5);
    
    // Ensure that 5 cards were dealt
    assert(deck.top == 5);  // Deck's top pointer should be 5 after dealing 5 cards

    // Check that the hand has valid cards (i.e., cards from the deck)
    assert(hand[0].value != 0);  // Ensure the first card is not a Joker
    assert(hand[4].value != 0);  // Ensure the last card is not a Joker

    printf("Deal cards test passed!\n");
}

// Main function to run all card management tests
int main() {
    test_generate_deck();
    test_shuffle_deck();
    test_deal_cards();

    printf("All tests passed!\n");
    return 0;
}
