#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include "card.h"

using namespace std;

// Forward declarations of supporting structures
class Gun;
struct Play;

class AIPlayer {
private:
    vector<Card> hand;
    Gun gun;
    int playerID;
    
    struct GameState {
        int currentLiarCard;
        int cardsInPile;
        vector<int> otherPlayersCardCount;
        vector<Play> playHistory;
        int totalPlayers;
        int remainingPlayers;
    };
    
    GameState currentState;  // Store current game state

    // Helper functions
    int calculateRemainingLiarCards(const GameState& state) {
        int totalLiarCards = (state.currentLiarCard == 0) ? 2 : 6;
        int playedCards = 0;
        
        for (const auto& play : state.playHistory) {
            if (play.getType() == Play::PlayType::PlayCards) {
                playedCards += play.getCardCount();
            }
        }
        
        for (const auto& card : hand) {
            if (card.getValue() == state.currentLiarCard) {
                playedCards++;
            }
        }
        
        return totalLiarCards - playedCards;
    }

    double calculateRiskFactor(const GameState& state) {
        double risk = 0.5;
        risk += (gun.getUsedChambers() * 0.1);
        
        if (state.remainingPlayers <= 2) {
            risk -= 0.2;
        }
        
        if (hand.size() <= 2) {
            risk -= 0.15;
        }
        
        return std::clamp(risk, 0.0, 1.0);
    }

    int decidePlayCount(int validCardsCount, const GameState& state) {
        if (state.remainingPlayers > 3) {
            return 1;
        }
        
        if (state.remainingPlayers <= 2) {
            return std::min(3, validCardsCount);
        }
        
        return std::min(2, validCardsCount);
    }

    bool shouldBluff(const GameState& state) {
        double bluffNecessity = 1.0 - (hand.size() / 5.0);
        
        if (state.remainingPlayers <= 2) {
            bluffNecessity += 0.2;
        }
        
        double gunRisk = gun.getUsedChambers() / 6.0;
        bluffNecessity -= gunRisk;
        
        return (bluffNecessity > 0.6);
    }

    int decideBluffCount(const GameState& state) {
        if (state.remainingPlayers > 3 || gun.getUsedChambers() >= 3) {
            return 1;
        }
        
        if (state.remainingPlayers <= 2) {
            return (rand() % 2) + 1;
        }
        
        return 1;
    }

    double adjustProbabilityByHistory(double baseProbability, const Play& play, const GameState& state) {
        int playerBluffCount = 0;
        int playerTotalPlays = 0;
        
        for (const auto& historicPlay : state.playHistory) {
            if (historicPlay.getPlayerID() == play.getPlayerID()) {
                playerTotalPlays++;
                if (historicPlay.wasBluff()) {
                    playerBluffCount++;
                }
            }
        }
        
        if (playerTotalPlays > 0) {
            double playerBluffRate = playerBluffCount / (double)playerTotalPlays;
            baseProbability = (baseProbability + playerBluffRate) / 2.0;
        }
        
        return baseProbability;
    }

    double adjustProbabilityBySituation(double baseProbability, const GameState& state) {
        if (state.remainingPlayers <= 2) {
            baseProbability += 0.1;
        }
        
        for (int cardCount : state.otherPlayersCardCount) {
            if (cardCount <= 2) {
                baseProbability += 0.15;
            }
        }
        
        return std::clamp(baseProbability, 0.0, 1.0);
    }

    vector<Card> getValidCardsForLiarCard(const vector<Card>& playerHand, int liarCard) {
        vector<Card> validCards;
        for (const auto& card : playerHand) {
            if (card.getValue() == liarCard || card.isJoker()) {
                validCards.push_back(card);
            }
        }
        return validCards;
    }

    // Added missing core decision functions
    bool shouldChallenge(const Play& lastPlay, const GameState& state) {
        if (lastPlay.getType() != Play::PlayType::PlayCards) {
            return false;
        }

        double baseProbability = 0.3; // Base suspicion level
        
        // Adjust for number of cards played
        baseProbability += (lastPlay.getCardCount() - 1) * 0.2;
        
        // Adjust based on remaining possible valid cards
        int remainingValidCards = calculateRemainingLiarCards(state);
        if (lastPlay.getCardCount() > remainingValidCards) {
            baseProbability += 0.4;
        }
        
        // Adjust based on player history
        baseProbability = adjustProbabilityByHistory(baseProbability, lastPlay, state);
        
        // Adjust based on game situation
        baseProbability = adjustProbabilityBySituation(baseProbability, state);
        
        // Final risk adjustment
        double riskFactor = calculateRiskFactor(state);
        
        return (baseProbability > riskFactor);
    }

    Play decidePlaying(const GameState& state) {
        vector<Card> validCards = getValidCardsForLiarCard(hand, state.currentLiarCard);
        
        if (validCards.empty() || shouldBluff(state)) {
            // Bluff
            int bluffCount = decideBluffCount(state);
            vector<Card> bluffCards;
            for (int i = 0; i < bluffCount && i < hand.size(); i++) {
                bluffCards.push_back(hand[i]);
            }
            return Play(Play::PlayType::PlayCards, bluffCards, playerID);
        } else {
            // Play valid cards
            int playCount = decidePlayCount(validCards.size(), state);
            vector<Card> playCards(validCards.begin(), validCards.begin() + playCount);
            return Play(Play::PlayType::PlayCards, playCards, playerID);
        }
    }

public:
    AIPlayer(int id) : playerID(id), gun() {}
    
    int getID() const { return playerID; }

    void addCard(const Card& card) {
        hand.push_back(card);
    }

    void removeCards(const vector<Card>& cards) {
        for (const auto& card : cards) {
            auto it = find(hand.begin(), hand.end(), card);
            if (it != hand.end()) {
                hand.erase(it);
            }
        }
    }

    int getHandSize() const { return hand.size(); }
    
    bool isEliminated() const { return gun.isEliminated(); }
    
    Gun getGun() const { return gun; }

    void handleDeathRoulette() {
        gun.pullTrigger();
    }

    Play makePlay(const GameState& state) {
        if (!state.playHistory.empty()) {
            if (shouldChallenge(state.playHistory.back(), state)) {
                return Play(Play::PlayType::Challenge, playerID);
            }
        }
        return decidePlaying(state);
    }

    void receiveCards(const vector<Card>& cards) {
        hand.insert(hand.end(), cards.begin(), cards.end());
    }

    void updateGameState(const GameState& newState) {
        currentState = newState;
    }

    vector<Card> getHand() const { return hand; }

    void reset() {
        hand.clear();
        gun = Gun();
    }

    void handleChallengeResult(bool wasSuccessful) {
        if (!wasSuccessful) {
            handleDeathRoulette();
        }
    }

    bool validatePlay(const Play& play) const {
        if (play.getType() == Play::PlayType::PlayCards) {
            return play.getCardCount() <= hand.size();
        }
        return true;
    }

    string toString() const {
        stringstream ss;
        ss << "AI Player " << playerID << "\n";
        ss << "Hand size: " << hand.size() << "\n";
        ss << "Gun chambers used: " << gun.getUsedChambers() << "\n";
        ss << "Eliminated: " << (isEliminated() ? "Yes" : "No");
        return ss.str();
    }
};

// Supporting structures
class Gun {
public:
    Gun() : usedChambers(0), eliminated(false) {}

    void pullTrigger() {
        usedChambers++;
        if (usedChambers >= 6) {
            eliminated = true;
        }
    }

    int getUsedChambers() const { return usedChambers; }
    bool isEliminated() const { return eliminated; }

private:
    int usedChambers;
    bool eliminated;
};

struct Play {
    enum class PlayType {
        Challenge,
        PlayCards
    };

    Play(PlayType type, int playerId = -1) 
        : type(type), playerID(playerId), cardCount(0) {}
    
    Play(PlayType type, const vector<Card>& cards, int playerId) 
        : type(type), playerID(playerId), playedCards(cards), cardCount(cards.size()) {}

    PlayType getType() const { return type; }
    int getPlayerID() const { return playerID; }
    int getCardCount() const { return cardCount; }
    vector<Card> getCards() const { return playedCards; }
    bool wasBluff() const { return bluffStatus; }
    void setBluffStatus(bool wasBluff) { bluffStatus = wasBluff; }

private:
    PlayType type;
    int playerID;
    vector<Card> playedCards;
    int cardCount;
    bool bluffStatus = false;
};

#endif // AIPLAYER_H
