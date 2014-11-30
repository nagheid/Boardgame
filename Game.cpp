#include <stdio.h>
#include <string>
#include <sstream>
#include <istream>
#include <iostream>
#include <vector>

#include "gameboard.h"
#include "player.h"
#include "tile.h"

template <const int N>
bool takeTurn(GameBoard<Tile, Player, N, N> &bg, const std::string& pName) {
	// TODO
	try {
		GameBoard<Tile, Player, N, N>::Move m = GameBoard<Tile, Player, N, N>::DOWN;
		cout << "Move = " << m << endl;
		cin.exceptions(std::istream::failbit);
		//cin >> m;
		const Tile t = bg.move(m, pName);

		Player p = bg.getPlayer(pName);
		if (p.canAct()) {
			bool makeAction;
			cin >> makeAction;
			if (makeAction) {
				//vector<Player> opL = bg.getPlayers(t);
			}
		}

		return true;
	} catch (std::istream::failure e) {
		cout << "Incorrect key pressed";
		cin.clear();
	} catch (std::out_of_range e) {
		cout << e.what();
	}
	
	return false;
}

template<typename T>
const T in_get(istream &in = std::cin) {
	T x;
	if (!(in >> x)) throw "Invalid input";
	return x;
}

int main() {
	// TODO
	// SETUP THE BOARD //

	// Input the names of all players
	// TODO can change the way we take in names; this is simple for now
	vector<string> playerNames;
	std::cout << "Name rules" << std::endl;
	std::cout << "1. no spaces in a player name, use '_'" << std::endl;
	std::cout << "2. use a space to separate more than one player name" << std::endl;
	std::cout << "3. player names must be unique\n" << std::endl;
	std::cout << "Please enter the player names separated by a space: " << std::endl;
	std::cout << "Press enter when done" << std::endl;
	string line, name;
	getline(std::cin, line);
	istringstream streamLine(line);
	while (streamLine >> name) {
		playerNames.push_back(name);
	}
	
	// Input the size of the board
	const int r = 6;
	const int c = 6;

	// Initialize a board game
	GameBoard<Tile, Player, r, c> bg(playerNames);

	// Initialize tiles
	TileFactory *tf = TileFactory::get(r*c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			bg.add(*(tf->next()), i, j);
		}
	}

	bg.setPlayers(); // playerNames);

	// Iterate over players
	for (auto pName : playerNames) {
		do {
			Player player = bg.getPlayer(pName);
			cout << player.getName() << endl;
		} while (! takeTurn<r>(bg, pName));
		if ( bg.win(pName) ) break;
	}
}