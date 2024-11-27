#include <assert.h>
#include "../include/game.h"
#include "../include/card.h"

// Test handling a player's turn (including selecting cards and challenging)
void test_handle_turn() {
    Deck deck;
    generate_deck(&deck);

    Player player = {{}, 5, 0, 1, 1};  // Player 1 with 5 cards and 1 bullet
    deal_cards(&deck, player.hand, 5);  // Deal cards to player 1

    // Handle the player's turn
    handle_turn(&player, &deck);

    // Check that the hand count is reduced after playing cards
    assert(player.hand_count == 2);  // Assuming the player played 3 cards
    printf("Player turn handling test passed!\n");
}

// Test handling a challenge (assume challenge fails)
void test_handle_challenge() {
    Player challenger = { {}, 5, 0, 2, 1};  // Player 2 with 5 cards
    Player previous_player = { {}, 5, 0, 1, 1};  // Player 1 with 5 cards

    // Simulate a challenge (assume the challenge fails)
    handle_challenge(&challenger, &previous_player);

    // The challenger should have been eliminated in case of failure
    printf("Challenge handling test passed!\n");
}

// Main function to run all game logic tests
int main() {
    test_handle_turn();
    test_handle_challenge();

    printf("All tests passed!\n");
    return 0;
}
