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
        int totalPlayers;        // Added: track total players
        int remainingPlayers;    // Added: track remaining players
    };

    // Added helper functions
    int calculateRemainingLiarCards(const GameState& state) {
        int totalLiarCards = (state.currentLiarCard == 0) ? 2 : 6; // Jokers or normal cards
        int playedCards = 0;
        
        // Count cards from play history
        for (const auto& play : state.playHistory) {
            if (play.getType() == PlayType::PlayCards) {
                playedCards += play.getCardCount();
            }
        }
        
        // Count cards in AI's hand that match liar card
        for (const auto& card : hand) {
            if (card.getValue() == state.currentLiarCard) {
                playedCards++;
            }
        }
        
        return totalLiarCards - playedCards;
    }

    double calculateRiskFactor(const GameState& state) {
        // Base risk starts at 0.5
        double risk = 0.5;
        
        // Adjust risk based on gun chambers
        risk += (gun.getUsedChambers() * 0.1); // Higher risk with more used chambers
        
        // Adjust risk based on game state
        if (state.remainingPlayers <= 2) {
            risk -= 0.2; // More aggressive in heads-up play
        }
        
        // Adjust risk based on hand size
        if (hand.size() <= 2) {
            risk -= 0.15; // More aggressive with few cards
        }
        
        return std::clamp(risk, 0.0, 1.0);
    }

    int decidePlayCount(int validCardsCount, const GameState& state) {
        // Conservative with 1 card if many players left
        if (state.remainingPlayers > 3) {
            return 1;
        }
        
        // More aggressive late game
        if (state.remainingPlayers <= 2) {
            return std::min(3, validCardsCount);
        }
        
        // Default to playing up to 2 cards
        return std::min(2, validCardsCount);
    }

    bool shouldBluff(const GameState& state) {
        // Calculate basic probability
        double bluffNecessity = 1.0 - (hand.size() / 5.0); // Higher necessity with fewer cards
        
        // Adjust based on game state
        if (state.remainingPlayers <= 2) {
            bluffNecessity += 0.2; // More likely to bluff in heads-up
        }
        
        // Adjust based on gun risk
        double gunRisk = gun.getUsedChambers() / 6.0;
        bluffNecessity -= gunRisk; // Less likely to bluff with higher gun risk
        
        return (bluffNecessity > 0.6);
    }

    int decideBluffCount(const GameState& state) {
        // Conservative bluffing
        if (state.remainingPlayers > 3 || gun.getUsedChambers() >= 3) {
            return 1;
        }
        
        // More aggressive in late game
        if (state.remainingPlayers <= 2) {
            return (rand() % 2) + 1; // 1 or 2 cards
        }
        
        return 1; // Default to 1 card
    }

    double adjustProbabilityByHistory(double baseProbability, const Play& play, const GameState& state) {
        // Analyze player patterns
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
        // Late game adjustment
        if (state.remainingPlayers <= 2) {
            baseProbability += 0.1; // Assume more bluffing in heads-up
        }
        
        // Desperate situation adjustment
        for (int cardCount : state.otherPlayersCardCount) {
            if (cardCount <= 2) {
                baseProbability += 0.15; // Assume more bluffing from players with few cards
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

public:
class AIPlayer {
private:
    // ... (previous private members and helper functions remain the same)

public:
    AIPlayer(int id) : playerID(id) {
        gun = Gun();  // Initialize with new gun
    }
    
    // Get player's ID
    int getID() const {
        return playerID;
    }

    // Add cards to hand
    void addCard(const Card& card) {
        hand.push_back(card);
    }

    // Remove cards from hand
    void removeCards(const vector<Card>& cards) {
        for (const auto& card : cards) {
            auto it = find(hand.begin(), hand.end(), card);
            if (it != hand.end()) {
                hand.erase(it);
            }
        }
    }

    // Get current hand size
    int getHandSize() const {
        return hand.size();
    }

    // Check if player is eliminated
    bool isEliminated() const {
        return gun.isEliminated();
    }

    // Get gun state
    Gun getGun() const {
        return gun;
    }

    // Handle death roulette result
    void handleDeathRoulette() {
        gun.pullTrigger();
    }

    // Main decision-making function
    Play makePlay(const GameState& state) {
        // First check if we should challenge the previous play
        if (!state.playHistory.empty()) {
            if (shouldChallenge(state.playHistory.back(), state)) {
                return Play(PlayType::Challenge, playerID);
            }
        }
        return decidePlaying(state);
    }

    // Handle receiving cards from lost challenge
    void receiveCards(const vector<Card>& cards) {
        for (const auto& card : cards) {
            hand.push_back(card);
        }
    }

    // Update game state information
    void updateGameState(const GameState& newState) {
        currentState = newState;
    }

    // Get player's current hand
    vector<Card> getHand() const {
        return hand;
    }

    // Reset player for new game
    void reset() {
        hand.clear();
        gun = Gun();
    }

    // Handle challenge results
    void handleChallengeResult(bool wasSuccessful) {
        if (!wasSuccessful) {
            handleDeathRoulette();
        }
    }

    // Validate play before making it
    bool validatePlay(const Play& play) const {
        if (play.getType() == PlayType::PlayCards) {
            return play.getCardCount() <= hand.size();
        }
        return true;
    }

    // Get string representation of player state (for debugging)
    string toString() const {
        stringstream ss;
        ss << "AI Player " << playerID << "\n";
        ss << "Hand size: " << hand.size() << "\n";
        ss << "Gun chambers used: " << gun.getUsedChambers() << "\n";
        ss << "Eliminated: " << (isEliminated() ? "Yes" : "No");
        return ss.str();
    }

private:
    GameState currentState;  // Store current game state
};

// Required supporting structures

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
};
