#include <stdio.h>
#include "rule.h"

void test_handle_challenge() {
    Player challenger = { .id = 1, .death_chamber = 0, .is_eliminated = false };
    Player current_player = { .id = 2, .num_played_cards = 2, .death_chamber = 0, .is_eliminated = false };
    
    current_player.played_cards[0] = (Card){2, false}; // Correct card
    current_player.played_cards[1] = (Card){3, false}; // Incorrect card
    
    int called_value = 2; // Declared value
    handle_challenge(&challenger, &current_player);
    
    printf("Test handle_challenge complete.\n");
}

int main() {
    test_handle_challenge();
    return 0;
}