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
    // ... (rest of the public interface remains the same)
};
