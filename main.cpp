#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "card.h"
#include "game.h"
#include "rule.h"
#include "realplayer.h"
#include "AI_Player.cpp"

using namespace std;

#define NUM_PLAYERS 4
#define NUM_CARDS_PER_PLAYER 5

extern int challenger_id;
extern int current_player_id;
extern int called_value;
extern bool is_bluff;

struct GamePlayer {
    string name;
    bool is_ai;
    Player* human;
    AIPlayer* ai;
    vector<Card> played_cards;
    int death_chamber;
};

void print_game_state(vector<GamePlayer>& players, int called_value) {
    cout << "\n=== Game State ===\n";
    cout << "Current card to play: " << 
        (called_value == 1 ? "Ace" : 
         called_value == 2 ? "King" : 
         called_value == 3 ? "Queen" : "Jack") << endl;

    for (size_t i = 0; i < players.size(); i++) {
        if (!(players[i].is_ai ? players[i].ai->isEliminated() : players[i].human->is_eliminated)) {  
            cout << players[i].name << " has " << 
                (players[i].is_ai ? players[i].ai->getHandSize() : players[i].human->hand_count) << 
                " cards\n";
        }
    }
    cout << "================\n\n";
}

void start_new_round(vector<GamePlayer>& players) {
    // Create fresh deck for new round
    Deck deck;
    generate_deck(&deck);
    shuffle_deck(&deck);

    // Generate new called value (1=Ace, 2=King, 3=Queen, 4=Jack)
    called_value = (rand() % 4) + 1;
    cout << "\nStarting new round!\n";
    
    // Clear all previous cards 
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (players[i].is_ai) {
            if (!players[i].ai->isEliminated()) {
                // Clear AI's hand by reinitializing
                players[i].ai = new AIPlayer(i);
                
                // Deal fresh 5 cards
                Card temp_hand[NUM_CARDS_PER_PLAYER];
                deal_cards(&deck, temp_hand, NUM_CARDS_PER_PLAYER);
                for (int j = 0; j < NUM_CARDS_PER_PLAYER; j++) {
                    temp_hand[j].is_joker = (temp_hand[j].value == 0);
                    players[i].ai->addCard(temp_hand[j]);
                }
            }
        } else if (!players[i].human->is_eliminated) {
            players[i].human->hand_count = 0;  // Clear all previous cards
            Card temp_hand[NUM_CARDS_PER_PLAYER];
            deal_cards(&deck, temp_hand, NUM_CARDS_PER_PLAYER);
            for (int j = 0; j < NUM_CARDS_PER_PLAYER; j++) {
                players[i].human->hand[j] = temp_hand[j];
                players[i].human->hand[j].is_joker = (temp_hand[j].value == 0);
                players[i].human->hand_count++;
            }
        }
        players[i].played_cards.clear();
    }
}

int main() {
    srand(time(NULL));
    
    // Initialize players
    vector<GamePlayer> players(NUM_PLAYERS);
    
    // Initialize human player
    players[0].human = new Player();
    players[0].is_ai = false;
    players[0].human->id = 0;
    players[0].human->death_chamber = 1;
    players[0].human->is_eliminated = false;
    cout << "Enter your name: ";
    cin >> players[0].human->name;
    players[0].name = players[0].human->name;

    // Initialize AI players
    for (int i = 1; i < NUM_PLAYERS; i++) {
        players[i].ai = new AIPlayer(i);
        players[i].is_ai = true;
        players[i].name = "AI_" + to_string(i);
        players[i].death_chamber = 1;
    }

    bool game_over = false;
    int current_turn = 0;

    while (!game_over) {
        start_new_round(players);
        bool round_over = false;

        while (!round_over) {
            print_game_state(players, called_value);

            if (current_turn == 0) {  // Human player's turn
                cout << "Your turn!\n";
                
                int prev_id = (NUM_PLAYERS + current_turn - 1) % NUM_PLAYERS;
                Player previous_player = Player();
                if (players[prev_id].is_ai) {
                    previous_player.id = prev_id;
                    previous_player.is_eliminated = players[prev_id].ai->isEliminated();
                    previous_player.death_chamber = players[prev_id].death_chamber;
                    previous_player.num_played_cards = players[prev_id].played_cards.size();
                    strncpy(previous_player.name, players[prev_id].name.c_str(), 49);
                    previous_player.name[49] = '\0';
                    
                    for (size_t i = 0; i < players[prev_id].played_cards.size(); i++) {
                        previous_player.played_cards[i] = players[prev_id].played_cards[i];
                    }
                } else {
                    previous_player = *players[prev_id].human;
                }

                players[0].human->num_played_cards = 0;
                challenger_id = 0;
                current_player_id = prev_id;

                handle_player_input(*(players[0].human), previous_player);

                if (players[0].human->is_eliminated) {
                    cout << "\nGame Over! You've been eliminated!\n";
                    game_over = true;
                    round_over = true;
                    break;
                }
                
                if (players[0].human->num_played_cards == 0) {  // Challenge was made
                    round_over = true;  // Start new round after challenge
                } else {
                    players[0].played_cards.clear();
                    for (int i = 0; i < players[0].human->num_played_cards; i++) {
                        players[0].played_cards.push_back(players[0].human->played_cards[i]);
                    }
                }
            } else {  // AI player's turn
                if (!players[current_turn].ai->isEliminated()) {
                    cout << "AI " << current_turn << "'s turn\n";
                    
                    AIPlayer::GameState state = {
                        .currentLiarCard = called_value,
                        .cardsInPile = 0,
                        .totalPlayers = NUM_PLAYERS,
                        .remainingPlayers = NUM_PLAYERS
                    };
                    
                    Play ai_play = players[current_turn].ai->makePlay(state);
                    
                    if (ai_play.getType() == Play::PlayType::Challenge) {
                        cout << "AI " << current_turn << " challenges!" << endl;
                        
                        int prev_player = (current_turn - 1 + NUM_PLAYERS) % NUM_PLAYERS;
                        challenger_id = current_turn;
                        current_player_id = prev_player;

                        Player challenger;
                        challenger.id = current_turn;
                        challenger.death_chamber = players[current_turn].death_chamber;

                        Player challenged;
                        challenged.id = prev_player;
                        challenged.death_chamber = players[prev_player].death_chamber;
                        challenged.num_played_cards = players[prev_player].played_cards.size();
                        for (size_t i = 0; i < players[prev_player].played_cards.size(); i++) {
                            challenged.played_cards[i] = players[prev_player].played_cards[i];
                        }

                        handle_challenge(&challenger, &challenged);

                        if (challenger.is_eliminated) {
                            players[current_turn].ai->setEliminated(true);
                        }
                        if (challenged.is_eliminated) {
                            if (prev_player == 0) {
                                players[0].human->is_eliminated = true;
                                cout << "\nGame Over! You've been eliminated!\n";
                                game_over = true;
                            } else {
                                players[prev_player].ai->setEliminated(true);
                            }
                        }
                        round_over = true;  // Start new round after challenge
                    } else {
                        vector<Card> played_cards = ai_play.getCards();
                        cout << "AI " << current_turn << " plays " << played_cards.size() << " card(s)" << endl;
                        players[current_turn].played_cards = played_cards;
                        players[current_turn].ai->removeCards(played_cards);
                    }
                }
            }

            if (!round_over) {
                current_turn = (current_turn + 1) % NUM_PLAYERS;
            }

            // Check if all AIs are eliminated (human wins)
            if (!players[0].human->is_eliminated) {
                bool all_ais_eliminated = true;
                for (int i = 1; i < NUM_PLAYERS; i++) {
                    if (!players[i].ai->isEliminated()) {
                        all_ais_eliminated = false;
                        break;
                    }
                }
                if (all_ais_eliminated) {
                    game_over = true;
                    round_over = true;
                    cout << "\nCongratulations! " << players[0].name << " wins!\n";
                }
            }
        }
    }

    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (players[i].is_ai) {
            delete players[i].ai;
        } else {
            delete players[i].human;
        }
    }

    return 0;
}
