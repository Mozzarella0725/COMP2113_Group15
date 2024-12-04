#ifndef REALPLAYER_H
#define REALPLAYER_H

#include "game.h"
#include "rule.h"
#include "card.h"
#include <string>

void option(string& command, Player previous_player);
void handle_player_input(Player& player, Player previous_player);

#endif
