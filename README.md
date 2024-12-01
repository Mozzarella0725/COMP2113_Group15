# COMP2113_Group15

#### Identification of the team members.

| Name        | UID        |
| ----------- | ---------- |
| Zhao Kexin  | 3035845368 |
| Tsang KaYin | 3036001842 |
| Zhang Muqun | 3036098065 |
| Wang Yiheng | 3036100222 |
| Zhou Yuguang| 3036002169 |
#### A description of your application.

##### 唬牌 - Liar's bar

1. 卡牌管理与生成 - zmq
   1. 生成
   2. 存储
   3. 发牌，抽牌
2. 玩家操作 - zjr
   1. 质疑与否
   2. 选择出牌
   3. 更新状态
3. 规则判定 - bot - wyh
   1. 质疑
   2. 选择出牌
   3. strategy
4. 回合管理 - zkx
   1. 实现流程
   2. 判定
   3. 进行**惩罚**
   4. 1/6
5. 主流程和整合 - zyg
   1. cheat code: 透视

### Liar's Deck Operation Instructions:

#### Basic Setup of Liar's Deck:

- The deck consists of 20 cards: 6 Aces, 6 Kings, 6 Queens, and 2 Jokers
- Jokers can substitute for any card
- 2-4 players participate, each starting with 5 cards
- Each player holds a revolver with 1 bullet randomly loaded in one of the 6 chambers
- Each player has a maximum of 30 seconds for thinking and decision-making

#### Game Process of Liar's Deck:

1. At the beginning of each round, the system designates the "liar's card" type for this round (e.g., "Ace").Liars Card
2. Players take turns playing cards, 1-3 cards each time. For example, throw out 2 cards means the player claims to have played 2 "Aces".Throw Cards
3. The next player can choose to:

- Believe the previous player's statement and play their own cards
- Challenge the previous player's play (Call Liar!), indicating "I don't believe you just played 2 'Aces'". Then the system reveals the pile to verify.
  - If the previous player didn't play 2 cards (e.g., 0 "Aces"), the challenge is successful, and the previous player undergoes a death roulette judgment;
  - If the previous player indeed played 2 "Aces" (including Jokers), the challenge fails, and the challenging player undergoes a death roulette judgment;Gun

4. Death roulette judgment means firing the gun at oneself. If it's an empty chamber, the game proceeds to the next round; if successful, the player is eliminated, and the game continues to the next round
5. The game continues until only one player remains, who becomes the winner.
