#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "game_state.h"
#include "relay.h"

using namespace std;

extern int challenger_id;
extern int current_player_id;
extern int called_value;
extern bool is_bluff;

bool check_all_players_but_one_empty(const vector<GamePlayer>& players, int& player_with_cards) {
    int count = 0;
    player_with_cards = -1;
    
    for (int i = 0; i < 4; i++) {
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
    vector<GamePlayer> players(4);
    
    // Initialize human player
    players[0].human = new Player();
    players[0].is_ai = false;
    players[0].human->id = 0;
    players[0].human->death_chamber = players[0].death_chamber = 1;
    cout << "Welcome to Liar's Bar!" << endl;
    cout << "Can you suivive to the end?" << endl;
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
                    // Last player with cards didn't challenge, they face death roulette
                    Player last_player;
                    last_player.id = player_with_cards;
                    last_player.death_chamber = players[player_with_cards].death_chamber;
                    last_player.is_eliminated = false;
                    strncpy(last_player.name, players[player_with_cards].name.c_str(), 49);
                    
                    relay_message(("All other players have emptied their hands. " + 
                        players[player_with_cards].name + " must face death roulette!\n").c_str());
                    
                    trigger_death_roulette(&last_player);
                    
                    if (last_player.is_eliminated) {
                        if (players[player_with_cards].is_ai) {
                            players[player_with_cards].ai->setEliminated(true);
                        } else {
                            players[player_with_cards].human->is_eliminated = true;
                            game_over = true;
                        }
                    }
                    players[player_with_cards].death_chamber = last_player.death_chamber;
                }
                round_over = true;
                continue;
            }

            // Skip if current player has no cards
            if ((players[current_turn].is_ai && players[current_turn].ai->getHandSize() == 0) ||
                (!players[current_turn].is_ai && players[current_turn].human->hand_count == 0)) {
                current_turn = (current_turn + 1) % 4;
                continue;
            }

            if (current_turn == 0) {  // Human turn
                Player temp_player;
                handle_player_input(*(players[0].human), temp_player);
                if (players[0].human->num_played_cards == 0) {
                    if (last_player_with_valid_cards != -1) {
                        handle_challenge(players, 0, last_player_with_valid_cards);
                        players[last_player_with_valid_cards].played_cards.clear();
                        round_over = true;
                    }
                } else {
                    players[0].played_cards.clear();
                    players[0].played_cards.assign(players[0].human->played_cards, 
                        players[0].human->played_cards + players[0].human->num_played_cards);
                    last_player_with_valid_cards = 0;
                }
            } else if (!players[current_turn].ai->isEliminated()) {  // AI turn
                relay_message(("AI " + to_string(current_turn) + "'s turn\n").c_str());
                Play ai_play = players[current_turn].ai->makePlay({called_value, 0, 4, 4});
                
                if (ai_play.getType() == Play::PlayType::Challenge) {
                    if (last_player_with_valid_cards != -1 && !players[last_player_with_valid_cards].played_cards.empty()) {
                        relay_message(("AI " + to_string(current_turn) + " challenges " + 
                            players[last_player_with_valid_cards].name + "!\n").c_str());
                        handle_challenge(players, current_turn, last_player_with_valid_cards);
                        players[last_player_with_valid_cards].played_cards.clear();
                        round_over = true;
                    }
                } else {
                    vector<Card> played_cards = ai_play.getCards();
                    relay_message(("AI " + to_string(current_turn) + " plays " + 
                        to_string(played_cards.size()) + " card(s)\n").c_str());
                    players[current_turn].played_cards.clear();
                    players[current_turn].played_cards = played_cards;
                    players[current_turn].ai->removeCards(played_cards);
                    last_player_with_valid_cards = current_turn;
                }
            }

            if (!round_over) {
                current_turn = (current_turn + 1) % 4;
            }

            // Check for win/lose conditions
            if (players[0].human->is_eliminated) {
                relay_message("\nGame Over! " );
                cout << "Pity on you!! \n Good luck in the next time!" << endl;
                game_over = true;
                break;
            }

            bool all_ais_eliminated = true;
            for (int i = 1; i < 4; i++) {
                if (!players[i].ai->isEliminated()) {
                    all_ais_eliminated = false;
                    break;
                }
            }
            if (all_ais_eliminated) {
                relay_message(("\nCongratulations! " + players[0].name + " wins!\n").c_str());
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
