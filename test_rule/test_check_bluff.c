#include <stdio.h>
#include "rule.h"

void test_check_bluff() {
    Card played_cards[3] = {
        {2, false},  // 2 of some suit
        {2, false},  // 2 of another suit
        {0, true}    // Joker
    };
    
    int result = check_bluff(played_cards, 3, 2);
    printf("Test check_bluff: %s\n", result ? "Passed" : "Failed");
}

int main() {
    test_check_bluff();
    return 0;
}