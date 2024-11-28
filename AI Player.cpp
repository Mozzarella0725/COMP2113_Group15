class AIPlayer {
private:
    vector<Card> hand;          // AI手牌
    Gun gun;                    // AI的手枪
    int playerID;               // AI玩家ID
    
    struct GameState {
        int currentLiarCard;    // 当前回合的"说谎牌"类型
        int cardsInPile;        // 当前牌堆数量
        vector<int> otherPlayersCardCount;  // 其他玩家手牌数
        vector<Play> playHistory;           // 出牌历史记录
    };

    // 决策辅助函数
    bool shouldChallenge(const Play& lastPlay, const GameState& state);
    Play decidePlaying(const GameState& state);
    double calculateBluffProbability(const Play& play, const GameState& state);

public:
    AIPlayer(int id) : playerID(id) {}
    
    Play makePlay(const GameState& state) {
        // 决定是否说谎或质疑
        if (!state.playHistory.empty()) {
            if (shouldChallenge(state.playHistory.back(), state)) {
                return Play(PlayType::Challenge);
            }
        }
        return decidePlaying(state);
    }

    bool shouldChallenge(const Play& lastPlay, const GameState& state) {
        // 基础判断逻辑
        int claimedCards = lastPlay.getCardCount();
        int remainingLiarCards = calculateRemainingLiarCards(state);
        
        // 如果声称的数量明显超过剩余可能的数量
        if (claimedCards > remainingLiarCards) {
            return true;
        }
        
        // 计算说谎概率
        double bluffProb = calculateBluffProbability(lastPlay, state);
        double riskFactor = calculateRiskFactor(state);
        
        return bluffProb > riskFactor;
    }

private:
    Play decidePlaying(const GameState& state) {
        vector<Card> validCards = getValidCardsForLiarCard(hand, state.currentLiarCard);
        
        // 如果手上有足够的真实卡牌，优先使用
        if (validCards.size() >= 1) {
            // 根据场上形势决定出牌数量
            int playCount = decidePlayCount(validCards.size(), state);
            return createPlay(PlayType::PlayCards, validCards, playCount);
        }
        
        // 需要说谎的情况
        if (shouldBluff(state)) {
            int bluffCount = decideBluffCount(state);
            return createBluffPlay(bluffCount, state);
        }
        
        // 保守策略：只出一张牌
        return createBluffPlay(1, state);
    }
    
    double calculateBluffProbability(const Play& play, const GameState& state) {
        // 基于以下因素计算说谎概率：
        // 1. 已知的牌
        // 2. 其他玩家的行为模式
        // 3. 剩余牌堆情况
        // 4. 当前回合进展
        double probability = 0.0;
        
        // 基础概率计算
        int claimedCards = play.getCardCount();
        int maxPossibleCards = calculateRemainingLiarCards(state);
        probability += (claimedCards / (double)maxPossibleCards);
        
        // 根据历史行为调整
        probability = adjustProbabilityByHistory(probability, play, state);
        
        // 根据当前局势调整
        probability = adjustProbabilityBySituation(probability, state);
        
        return probability;
    }
};
