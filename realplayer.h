#ifndef REALPLAYER_H
#define REALPLAYER_H

#include "card.h"

void display_player_hand(Card* player_hand, int player_hand_count);//展示手牌
void handle_player_input(Card* player_hand, int& player_hand_count);//处理玩家输入（出牌，跳过，退出游戏）

#endif
