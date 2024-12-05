#include <vector>
#include <random>
#include <algorithm>
#include "card.h"

class Play {
public:
    enum class PlayType { Regular, Challenge };
    
    Play(PlayType type, std::vector<Card> cards = std::vector<Card>()) 
        : type(type), cards(cards) {}
    
    PlayType getType() const { return type; }
    std::vector<Card> getCards() const { return cards; }

private:
    PlayType type;
    std::vector<Card> cards;
};

class AIPlayer {
public:
    struct GameState {
        int currentLiarCard;
        int cardsInPile;
        int totalPlayers;
        int remainingPlayers;
    };

    AIPlayer(int id) : playerId(id), eliminated(false) {}

    bool isEliminated() const {
        return eliminated;
    }

    void setEliminated(bool state) {
        eliminated = state;
    }

    int getHandSize() const {
        return hand.size();
    }

    void addCard(Card card) {
        hand.push_back(card);
    }

    void removeCards(const std::vector<Card>& cards) {
        for (const Card& card : cards) {
            auto it = std::find_if(hand.begin(), hand.end(),
                [&card](const Card& c) {
                    return c.value == card.value && c.is_joker == card.is_joker;
                });
            if (it != hand.end()) {
                hand.erase(it);
            }
        }
    }

    Play makePlay(const GameState& state) {
        // Calculate probability of being challenged
        float challengeRisk = calculateChallengeRisk(state);
        
        // Decide whether to challenge the previous play
        if (shouldChallenge(state)) {
            return Play(Play::PlayType::Challenge);
        }

        // Decide which cards to play
        std::vector<Card> cardsToPlay = selectCardsToPlay(state);
        return Play(Play::PlayType::Regular, cardsToPlay);
    }

    void handleChallengeResult(bool wasSuccessful) {
        // Update AI's strategy based on challenge results
        challengeHistory.push_back(wasSuccessful);
    }

private:
    int playerId;
    bool eliminated;
    std::vector<Card> hand;
    std::vector<bool> challengeHistory;
    
    float calculateChallengeRisk(const GameState& state) {
        // Base risk on number of matching cards in hand
        int matchingCards = std::count_if(hand.begin(), hand.end(),
            [state](const Card& c) { return c.value == state.currentLiarCard || c.is_joker; });
        
        return 1.0f - (float)matchingCards / hand.size();
    }

   bool shouldChallenge(const GameState& state) {
    // 降低 challengeThreshold 
    float challengeThreshold = 0.3f; // 从0.7改为0.3
    
    // 根据游戏状态调整挑战概率
    float challengeProbability = 0.0f;
    
    // 计算基础挑战概率
    float riskFactor = calculateChallengeRisk(state);
    
    ：
    // 1. 牌堆中的牌数较多
    float pileFactor = std::min(state.cardsInPile / 5.0f, 1.0f);
    
    // 2. 游戏接近尾声（剩余玩家较少）
    float playersFactor = 1.0f - (float)state.remainingPlayers / state.totalPlayers;
    
    // 3. 手牌中匹配当前声明的牌较少
    challengeProbability = riskFactor * 0.4f + // 风险因素权重
                          pileFactor * 0.3f +   // 牌堆因素权重
                          playersFactor * 0.3f; // 玩家因素权重
    
    float random = (float)rand() / RAND_MAX;
    
    // 当计算出的挑战概率高于阈值时更容易发起挑战
    return random < challengeProbability || 
           (random > challengeThreshold && riskFactor > 0.6f); //从0.8改为0.6
}

    std::vector<Card> selectCardsToPlay(const GameState& state) {
        std::vector<Card> cardsToPlay;
        std::vector<Card> matchingCards;
        std::vector<Card> nonMatchingCards;

        // Separate matching and non-matching cards
        for (const Card& card : hand) {
            if (card.value == state.currentLiarCard || card.is_joker) {
                matchingCards.push_back(card);
            } else {
                nonMatchingCards.push_back(card);
            }
        }

        // Decide number of cards to play (1-3)
        int numCardsToPlay = 1 + (rand() % std::min(3, (int)hand.size()));

        // If we have matching cards, prefer playing them
        if (!matchingCards.empty()) {
            for (int i = 0; i < std::min(numCardsToPlay, (int)matchingCards.size()); i++) {
                cardsToPlay.push_back(matchingCards[i]);
            }
        }

        // If we need more cards, bluff with non-matching cards
        while (cardsToPlay.size() < numCardsToPlay && !nonMatchingCards.empty()) {
            int index = rand() % nonMatchingCards.size();
            cardsToPlay.push_back(nonMatchingCards[index]);
            nonMatchingCards.erase(nonMatchingCards.begin() + index);
        }

        return cardsToPlay;
    }
};
