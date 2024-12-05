#ifndef REALPLAYER_H
#define REALPLAYER_H

#include "game.h"
#include "rule.h"
#include "card.h"
#include <string>

void handle_player_input(Player& player, Player previous_player);

struct PlayedCard {
    int num_played_cards;
};
extern PlayedCard playedcard; 
#endif
