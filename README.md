# COMP2113_Group15

## Identification of the team members

| Name         | UID        | Job Division                                                                                                                                                                     |
| ------------ | ---------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Zhao Kexin   | 3035845368 | Responsible for verifying the player or AI's card claim, judging whether the bluff is successful, and triggering the Roulette of death. Responsible for editing the README file. |
| Tsang KaYin  | 3036001842 | Responsible for managing the hand, interaction logic and status updates of live players.                                                                                         |
| Zhang Muqun  | 3036098065 | Responsible for card generation, shuffling, dealing, and special handling of Joker cards.                                                                                        |
| Wang Yiheng  | 3036100222 | Responsible for the logic of the three AI players, including bluff and flop decisions                                                                                            |
| Zhou Yuguang | 3036002169 | Responsible for the integration of all modules, control of the game flow, including turn management and decision.                                                                |

## Description

Liar's Deck is a card-based bluffing game where your goal is to outwit the AI players and survive until the end. Strategize carefully when selecting cards to play, master the art of deception, and call out the lies of your opponents!

### Key Features

1. Enter your name and compete against AI players in a battle of strategy and luck.
2. Bluff your way to victory while detecting the lies of others.
3. Survive the deadly Death Roulette and emerge as the last player standing.

---

## Basic Setup of Liar's Deck

- **Deck Composition**: The deck contains 20 cards:
  - 6 Aces, 6 Kings, 6 Queens, and 2 Jokers.
  - Jokers can substitute for any card.
- **Players**: 4 players, each starting with 5 cards.
- **Revolver**: Each player holds a revolver with 1 bullet randomly loaded in one of 6 chambers.

---

## Game Process

1. **Start of Round**: At the beginning of each round, the system designates the main deck type (e.g., "Ace").
2. **Playing Cards**: Players take turns playing 1-3 cards. For example, a player may claim, "I played 2 Aces."
3. **Next Player Options**:
   - **Believe**: Accept the previous player's statement and play your own cards.
   - **Challenge**: Call out a bluff by saying, "I don't believe you just played 2 Aces." The system will verify the pile:
     - **If bluffing**: The challenge is successful, and the previous player undergoes a Death Roulette judgment.
     - **If truthful**: The challenge fails, and the challenging player undergoes a Death Roulette judgment.
4. **Death Roulette**: Players fire the gun at themselves:
   - If the chamber is empty, the player survives, and the probability of death increases in subsequent rounds.
   - If the chamber is loaded, the player is eliminated.
5. **Victory Condition**: The game continues until only one player remains, who is declared the winner.

---

## Code Requirements Satisfied

1. **Random Event Generation**:

   - Death Roulette uses randomization with increasing probability for elimination.
2. **Data Structures**:

   - `Card` structure stores suit information for each card.
   - `Player` structure manages player data, including cards, chamber counts, and survival state.
3. **Dynamic Memory Management**:

   - `current_player` dynamically stores the data of the player currently taking their turn.
   - `challenger` dynamically stores the data of the challenging player.
4. **File Input and Output**:

   - The game prints the current state, including the main deck and the number of cards each player holds.
   - Prompts guide players through their next actions, such as choosing cards or making challenges.
   - The results of each challenge, including whether the Death Roulette is triggered, are displayed.
   - Player inputs are recorded to determine the next action and cards to play.
5. **Modular Program Design**:

   - Separate header files define structures and declare functions.
   - Functional components of the game are implemented in distinct files.
   - Test code is organized in a dedicated folder for clarity.
6. **Coding Standards**:

   - Functions include detailed comments describing their purpose and functionality.
   - Inline annotations explain how each code block operates.
   - Proper indentation and meaningful naming conventions ensure readability and maintainability.

---

## Quick Start Guide

Follow these steps to get started with Liar's Deck:

1. **Download**: Clone or download the repository and ensure all files are in the same directory.
2. **Compile**: Open a terminal, navigate to the directory, and type:

   ```bash
   make
   ```

3. **Run the Game**: Start the game by typing:

   ```bash
   ./game
   ```

4. **Play**: Follow the on-screen instructions to play. The game will automatically exit when you win or lose.
5. **Clean Up**: After playing, delete unnecessary files by typing:

   ```bash
   make clean
   ```

---

**Enjoy the game and may the best liar win!**
