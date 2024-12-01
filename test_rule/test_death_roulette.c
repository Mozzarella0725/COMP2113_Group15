#include <stdio.h>
#include "rule.h"

void test_trigger_death_roulette() {
    Player player = { .id = 3, .death_chamber = 2, .is_eliminated = false };
    
    trigger_death_roulette(&player);
    
    printf("Test trigger_death_roulette complete. Player eliminated: %s\n", 
           player.is_eliminated ? "Yes" : "No");
}

int main() {
    test_trigger_death_roulette();
    return 0;
}