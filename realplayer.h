#ifndef REALPLAYER_H
#define REALPLAYER_H

#include "card.h"

void display_player_hand(Card* player_hand, int num_player_cards);
void handle_player_input(Card* player_hand, int& num_player_cards);

#endif
