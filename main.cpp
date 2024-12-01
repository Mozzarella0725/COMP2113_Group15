#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "game.h"      // game management 
#include "card.h"      // Card and Deck structures
#include "realplayer.h" // human player 
#include "rule.h"      // game rules
#include "AI Player.cpp"  // AI player 

#define NUM_PLAYERS 4
#define NUM_HUMAN_PLAYERS 1
#define NUM_AI_PLAYERS 3
#define NUM_CARDS_PER_PLAYER 5

using namespace std;

extern int called_value;      // rule.c
extern bool is_bluff;        
extern int challenger_id;     
extern int current_player_id; 

struct GamePlayer {
    Player* human;           // player.h
    AIPlayer* ai;           //  AI Player.cpp
    bool is_ai;
    string name;
};

void print_game_state(vector<GamePlayer>& players) {
    cout << "\n=== Game State ===\n";
    for (size_t i = 0; i < players.size(); i++) {
        if (!(players[i].is_ai ? 
            players[i].ai->isEliminated() :     //  AI Player.cpp
            players[i].human->is_eliminated)) {  // player.h
            cout << players[i].name << " has " << 
                (players[i].is_ai ? 
                    players[i].ai->getHandSize() :   // AI Player.cpp
                    players[i].human->hand_count) << //  player.h
                " cards\n";
        }
    }
    cout << "================\n\n";
}

void run_game() {
    srand(time(NULL));

    /* Initialize deck  card.c */
    Deck deck;                   
    generate_deck(&deck);        
    shuffle_deck(&deck);         

    vector<GamePlayer> players(NUM_PLAYERS);
    
    /* Initialize human player player.h */
    players[0].human = new Player();  
    players[0].is_ai = false;
    players[0].human->id = 1;
    players[0].human->death_chamber = 1;
    players[0].human->is_eliminated = false;
    cout << "Enter your name: ";
    cin >> players[0].human->name;
    players[0].name = players[0].human->name;
    deal_cards(&deck, players[0].human->hand, NUM_CARDS_PER_PLAYER);  // Function from card.c

    /* Initialize AI players  AI Player.cpp */
    for (int i = 1; i < NUM_PLAYERS; i++) {
        players[i].ai = new AIPlayer(i + 1);    
        players[i].is_ai = true;
        players[i].name = "AI_" + to_string(i);
        
        /* Deal cards to AI  card.c and AIPlayer.cpp */
        Card temp_hand[NUM_CARDS_PER_PLAYER];   //  card.h
        deal_cards(&deck, temp_hand, NUM_CARDS_PER_PLAYER);  //  card.c
        for (int j = 0; j < NUM_CARDS_PER_PLAYER; j++) {
            players[i].ai->addCard(temp_hand[j]);  //  AIPlayer.cpp
        }
    }

    cout << "\nGame Start!\n";
    cout << "You are playing against 3 AI players\n";
    cout << "Remember: Type 'hku is brilliant' during your turn to see other players' cards!\n\n";

    /* Game loop */
    current_player_id = 0;
    bool game_over = false;

    while (!game_over) {
        /* Set liar's card , rule.c */
        called_value = (rand() % 3) + 1;  // rule.c
        string card_name;
        switch(called_value) {
            case 1: card_name = "Ace"; break;
            case 2: card_name = "King"; break;
            case 3: card_name = "Queen"; break;
        }
        
        cout << "\n=== New Round ===\n";
        cout << "Liar's card for this round: " << card_name << "\n";

        print_game_state(players);

        GamePlayer& current_player = players[current_player_id];
        
        if (current_player.is_ai) {
            /* AI player turn ,  AIPlayer.cpp  */
            if (!current_player.ai->isEliminated()) {  //  from AIPlayer.h
                cout << "\n" << current_player.name << "'s turn\n";
                
                /* Create game state using struct from AIPlayer.cpp */
                AIPlayer::GameState state;  //  AIPlayer.cpp
                state.currentLiarCard = called_value;
                state.cardsInPile = 0;
                state.totalPlayers = NUM_PLAYERS;
                state.remainingPlayers = NUM_PLAYERS;
                
                /* Get AI's play decision using AIPlayer.h */
                Play ai_play = current_player.ai->makePlay(state);  //  from AIPlayer.cpp
                
                if (ai_play.getType() == Play::PlayType::Challenge) {  //  from AIPlayer.cpp
                    cout << current_player.name << " challenges the previous play!\n";
                    int prev_id = (current_player_id + NUM_PLAYERS - 1) % NUM_PLAYERS;
                    if (!players[prev_id].is_ai) {
                        handle_challenge(nullptr, players[prev_id].human);  //  from rule.c
                    } else {
                        bool challenge_success = (rand() % 2) == 0;
                        current_player.ai->handleChallengeResult(challenge_success);  //  AIPlayer.cpp
                    }
                } else {
                    vector<Card> played_cards = ai_play.getCards();  //  AIPlayer.cpp
                    cout << current_player.name << " plays " << played_cards.size() << " cards\n";
                    current_player.ai->removeCards(played_cards);  //  AIPlayer.cpp
                }
            }
        } else {
            /* Human player turn, realplayer.cpp  */
            if (!current_player.human->is_eliminated) {
                handle_turn(current_player.human, &deck);  // From game.h
                
                int prev_id = (current_player_id + NUM_PLAYERS - 1) % NUM_PLAYERS;
                Player* previous_player = players[prev_id].is_ai ? 
                    nullptr : players[prev_id].human;
                
                handle_player_input(*current_player.human, *previous_player);  // From realplayer.cpp
            }
        }

        /* game over ? */
        int active_players = 0;
        int last_active = -1;
        
        for (int i = 0; i < NUM_PLAYERS; i++) {
            bool is_eliminated = players[i].is_ai ? 
                players[i].ai->isEliminated() :     //  AIPlayer.cpp
                players[i].human->is_eliminated;    //  player.h
                
            if (!is_eliminated) {
                active_players++;
                last_active = i;
            }
        }

        if (active_players == 1) {
            game_over = true;
            cout << "\n🎉 " << players[last_active].name << " wins the game! 🎉\n";
        } else {
            /* Move*/
            do {
                current_player_id = (current_player_id + 1) % NUM_PLAYERS;
            } while (players[current_player_id].is_ai ? 
                    players[current_player_id].ai->isEliminated() :     //  AIPlayer.cpp
                    players[current_player_id].human->is_eliminated);    //  player.h
        }
    }

    /* Clean */
    for (auto& player : players) {
        if (player.is_ai) {
            delete player.ai;
        } else {
            delete player.human;
        }
    }

    cout << "\nGame Over!\n";
    cout << "Thanks for playing Liar's Deck!\n";
}

int main() {
    run_game();
    return 0;
}
