#include "game_state.h"
#include "relay.h"
#include "card.h"
#include "rule.h"
#include "AI_Player.cpp"
#include <cstring>

extern int called_value;

void start_new_round(std::vector<GamePlayer>& players) {
    Deck deck;
    generate_deck(&deck);
    shuffle_deck(&deck);
    called_value = (rand() % 3) + 1;  // 1 = Ace, 2 = King, 3 = Queen
    relay_message("\nStarting new round!\n");
    
    // Deal cards to players
    for (int i = 0; i < 4; i++) {
        if (players[i].is_ai) {
            if (!players[i].ai->isEliminated()) {
                players[i].ai = new AIPlayer(i);
                Card temp_hand[5];
                deal_cards(&deck, temp_hand, 5);
                for (int j = 0; j < 5; j++) {
                    temp_hand[j].is_joker = (temp_hand[j].value == 0);
                    players[i].ai->addCard(temp_hand[j]);
                }
            }
        } else {
            if (!players[i].human->is_eliminated) {
                players[i].human->hand_count = 0;
                Card temp_hand[5];
                deal_cards(&deck, temp_hand, 5);
                for (int j = 0; j < 5; j++) {
                    players[i].human->hand[j] = temp_hand[j];
                    players[i].human->hand[j].is_joker = (temp_hand[j].value == 0);
                    players[i].human->hand_count++;
                }
            }
        }
        players[i].played_cards.clear();
    }
}

void print_game_state(std::vector<GamePlayer>& players) {
    relay_message("\n=== Game State ===\n");
    
    std::string card_name;
    switch(called_value) {
        case 1: card_name = "Ace"; break;
        case 2: card_name = "King"; break;
        case 3: card_name = "Queen"; break;
        default: card_name = "Unknown";
    }
    
    relay_message(("Current card to play: " + card_name + "\n").c_str());

    for (int i = 0; i < 4; i++) {
        bool is_eliminated;
        int card_count;
        
        if (players[i].is_ai) {
            is_eliminated = players[i].ai->isEliminated();
            card_count = players[i].ai->getHandSize();
        } else {
            is_eliminated = players[i].human->is_eliminated;
            card_count = players[i].human->hand_count;
        }
        
        if (!is_eliminated) {
            relay_message((players[i].name + " has " + 
                std::to_string(card_count) + " cards\n").c_str());
        }
    }
    relay_message("================\n\n");
}

void handle_challenge(std::vector<GamePlayer>& players, int challenger, int challenged) {
    Player challenger_player, challenged_player;
    
    // Initialize challenger
    challenger_player.id = challenger;
    challenger_player.death_chamber = players[challenger].death_chamber;
    challenger_player.is_eliminated = false;
    challenger_player.num_played_cards = 0;
    strncpy(challenger_player.name, players[challenger].name.c_str(), 49);
    challenger_player.name[49] = '\0';
    
    
    // Copy played cards from challenged player
    for (size_t i = 0; i < players[challenged].played_cards.size() && i < MAX_CARDS; i++) {
        challenged_player.played_cards[i] = players[challenged].played_cards[i];
    }

    // Handle the challenge
    handle_challenge(&challenger_player, &challenged_player);

    // Update death chambers
    if (challenger_player.is_eliminated) {
        players[challenger].death_chamber = challenger_player.death_chamber;
        if (players[challenger].is_ai) {
            players[challenger].ai->setEliminated(true);
        } else {
            players[challenger].human->is_eliminated = true;
        }
    }
