#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <string>
#include "card.h"
#include "game.h"
#include "rule.h"
#include "realplayer.h"

#define MAX_PLAYERS 4
#define MAX_CARDS 5

// Forward declare AIPlayer
class AIPlayer;

// Structure to hold player information
struct GamePlayer {
    std::string name;
    bool is_ai;
    Player* human;
    AIPlayer* ai;
    std::vector<Card> played_cards;
    int death_chamber;

    // Constructor
    GamePlayer() : is_ai(false), human(nullptr), ai(nullptr), death_chamber(1) {}
};

void start_new_round(std::vector<GamePlayer>& players);
void print_game_state(std::vector<GamePlayer>& players);
void handle_challenge(std::vector<GamePlayer>& players, int challenger, int challenged);

#endif 
