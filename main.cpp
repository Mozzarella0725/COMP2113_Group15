#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "game_state.h"
#include "relay.h"
#include "rule.h"
#include "realplayer.h"
#include "AI_Player.cpp"  

using namespace std;

extern int challenger_id;
extern int current_player_id;
extern bool is_bluff;

bool check_all_players_but_one_empty(const vector<GamePlayer>& players, int& player_with_cards) {
    int count = 0;
    player_with_cards = -1;
    
    for (size_t i = 0; i < players.size(); i++) {
        int cards = players[i].is_ai ? players[i].ai->getHandSize() : players[i].human->hand_count;
        if (cards > 0) {
            count++;
            player_with_cards = i;
        }
    }
    return count == 1;
}

int main() {
    srand(time(NULL));
    vector<GamePlayer> players;
    players.resize(4);
    
    // Initialize human player
    players[0].human = new Player();
    players[0].is_ai = false;
    players[0].human->id = 0;
    players[0].human->death_chamber = players[0].death_chamber = 1;
    relay_message("Enter your name: ");
    cin >> players[0].human->name;
    players[0].name = players[0].human->name;

    // Initialize AI players
    for (int i = 1; i < 4; i++) {
        players[i].ai = new AIPlayer(i);
        players[i].is_ai = true;
        players[i].name = "AI_" + to_string(i);
        players[i].death_chamber = 1;
    }

    bool game_over = false;
    int current_turn = 0;
    int last_player_with_valid_cards = -1;

    while (!game_over) {
        start_new_round(players);
        bool round_over = false;
        last_player_with_valid_cards = -1;

        while (!round_over) {
            print_game_state(players);

            // Check if only one player has cards left
            int player_with_cards;
            if (check_all_players_but_one_empty(players, player_with_cards)) {
                if (last_player_with_valid_cards != -1 && !players[last_player_with_valid_cards].played_cards.empty()) {
                    Player last_player;  
                    last_player.id = player_with_cards;
                    last_player.death_chamber = players[player_with_cards].death_chamber;
                    last_player.is_eliminated = false;
                    strncpy(last_player.name, players[player_with_cards].name.c_str(), 49);
                    
                    relay_message(("All other players have emptied their hands. " + 
                        players[player_with_cards].name + " must face death roulette!\n").c_str());
                    
                    trigger_death_roulette(&last_player);
                    
                    players[player_with_cards].death_chamber = last_player.death_chamber;
                    if (last_player.is_eliminated) {
                        if (players[player_with_cards].is_ai) {
                            delete players[player_with_cards].ai;
                            players.erase(players.begin() + player_with_cards);
                            if (current_turn > player_with_cards) {
                                current_turn--;
                            }
                        } else {
                            players.erase(players.begin() + player_with_cards);
                            game_over = true;
                        }
                    }
                }
                round_over = true;
                continue;
            }

            // Skip if current player has no cards
            if ((players[current_turn].is_ai && players[current_turn].ai->getHandSize() == 0) ||
                (!players[current_turn].is_ai && players[current_turn].human->hand_count == 0)) {
                current_turn = (current_turn + 1) % players.size();
                continue;
            }

            if (current_turn == 0) {  // Human turn
                Player* temp_player = new Player();  
                if (last_player_with_valid_cards != -1) {
                    temp_player->id = last_player_with_valid_cards;
                    strcpy(temp_player->name, players[last_player_with_valid_cards].name.c_str());
                    temp_player->num_played_cards = players[last_player_with_valid_cards].played_cards.size();
                    for (size_t i = 0; i < players[last_player_with_valid_cards].played_cards.size(); i++) {
                        temp_player->played_cards[i] = players[last_player_with_valid_cards].played_cards[i];
                    }
                } else {
                    temp_player->num_played_cards = 0;
                }
    
                handle_player_input(*(players[0].human), *temp_player);
                
                if (temp_player->is_eliminated) {
                    players.erase(players.begin());
                    game_over = true;
                } else if (playedcard.num_played_cards == 0) {
                    if (last_player_with_valid_cards != -1) {
                        round_over = true;
                    }
                } else {
                    players[0].played_cards.clear();
                    players[0].played_cards.assign(players[0].human->played_cards, 
                        players[0].human->played_cards + players[0].human->num_played_cards);
                    last_player_with_valid_cards = 0;
                }
                delete temp_player;
                
                if (round_over) continue;
                
            } else {  // AI turn
                string ai_name = players[current_turn].name;
                relay_message((ai_name + "'s turn\n").c_str());
                Play ai_play = players[current_turn].ai->makePlay({called_value, 0, 
                    static_cast<int>(players.size()), current_turn});
    
                if (ai_play.getType() == Play::PlayType::Challenge) {
                    if (last_player_with_valid_cards != -1 && !players[last_player_with_valid_cards].played_cards.empty()) {
                        relay_message((ai_name + " challenges " + 
                            players[last_player_with_valid_cards].name + "!\n").c_str());

                        Player* temp_ai = new Player();
                        temp_ai->id = current_turn;
                        temp_ai->death_chamber = players[current_turn].death_chamber;
                        strcpy(temp_ai->name, players[current_turn].name.c_str());

                        Player* last_player = new Player();
                        last_player->id = last_player_with_valid_cards;
                        last_player->death_chamber = players[last_player_with_valid_cards].death_chamber;
                        strcpy(last_player->name, players[last_player_with_valid_cards].name.c_str());

                        last_player->num_played_cards = players[last_player_with_valid_cards].human->num_played_cards;
                        memcpy(last_player->played_cards, players[last_player_with_valid_cards].human->played_cards, 
                            sizeof(Card) * last_player->num_played_cards);

                        handle_challenge(temp_ai, last_player);
                        
                        if (temp_ai->is_eliminated) {
                            delete players[current_turn].ai;  
                            players.erase(players.begin() + current_turn);
                            if (last_player_with_valid_cards > current_turn) {
                                last_player_with_valid_cards--;
                            }
                        }

                        delete temp_ai;
                        delete last_player;
                        players[last_player_with_valid_cards].played_cards.clear();
                        round_over = true;
                    }
                } else {
                    vector<Card> played_cards = ai_play.getCards();
                    relay_message((ai_name + " plays " + 
                        to_string(played_cards.size()) + " card(s)\n").c_str());
                    players[current_turn].played_cards.clear();
                    players[current_turn].played_cards = played_cards;
                    players[current_turn].ai->removeCards(played_cards);
                    last_player_with_valid_cards = current_turn;
                }
            }

            if (!round_over) {
                current_turn = (current_turn + 1) % players.size();
            }

            // Check for win/lose conditions
            if (players.size() == 1) {
                if (!players[0].is_ai) {
                    relay_message(("\nCongratulations! " + players[0].name + " wins!\n").c_str());
                } else {
                    relay_message(("\nGame Over! " + players[0].name + " wins!\n").c_str());
                }
                game_over = true;
                break;
            }
        }
    }

    // Cleanup
    for (auto& p : players) {
        if (p.is_ai) delete p.ai;
        else delete p.human;
    }
    return 0;
}
