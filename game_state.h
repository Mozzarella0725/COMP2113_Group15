#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <string>
#include "card.h"
#include "realplayer.h"

class AIPlayer;

struct GamePlayer {
    bool is_ai;
    std::string name;
    union {
        AIPlayer* ai;
        Player* human;
    };
    int death_chamber;
    std::vector<Card> played_cards;
};

void start_new_round(std::vector<GamePlayer>& players);
void print_game_state(std::vector<GamePlayer>& players);

extern int called_value;

#endif
