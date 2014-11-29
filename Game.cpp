#include "gameboard.h"
//#include "player.h"
#include "tile.h"

const int N = 1;

#define GAMEBOARD GameBoard<Tile, Player, N, N>

template <const int N>
bool takeTurn(GAMEBOARD &bg, const std::string& pName) {
	// TODO
	return false;
}

int main() {
	// TODO
	// Setup the board
	vector<string> playerNames;
	// TODO take input player names
	// TODO take input 'N'
	//N << std::cin;

	GAMEBOARD bg = GAMEBOARD(playerNames);

	// Iterate over players
	for (auto pName : playerNames) {
		do {
			//std::cout << bg.getPlayer(pName);
		} while (! takeTurn(bg, pName));
		//if ( bg.win(pName) ) break;
	}
}