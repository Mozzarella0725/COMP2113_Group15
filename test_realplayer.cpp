#include "realplayer.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
  while (true) {
    if (player_hand_count == 0) {
      cout << "You have no cards left in your hand. Your turn will be skipped" << endl;
      cout << "Skipping your turn..." << endl;
      break;
    }
    display_player_hand(player_hand, player_hand_count)
    handle_player_input(player_hand, player_hand_count)
  }
  return 0;
}
