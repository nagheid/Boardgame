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
	try {
		// Display player status
		Player p = bg.getPlayer(pName);
		cout << p << endl;

		// Input move
		cout << "Please enter one of the following values:" << endl;
		cout << "0(UP), 1(DOWN), 2(LEFT), 3(RIGHT)" << endl;
		cin.exceptions(std::istream::failbit); 
		int intM; cin >> intM;

		std::map<int, GameBoard<Tile, Player, N, N>::Move> map;
		map[0] = GameBoard<Tile, Player, N, N>::UP;
		map[1] = GameBoard<Tile, Player, N, N>::DOWN;
		map[2] = GameBoard<Tile, Player, N, N>::LEFT;
		map[3] = GameBoard<Tile, Player, N, N>::RIGHT;

		GameBoard<Tile, Player, N, N>::Move m = map[intM];
		cout << "Player pick move: " << m << endl;

		// TODO check if move is valid

		// Move player to tile
		Tile& old_tile = (Tile&)bg.getTile(pName);
		cout << "Player was on tile:\t" << old_tile << endl; 

		Tile& t = (Tile&)bg.move(m, pName);
		cout << "Player is now on tile:\t" << t << endl;

		// If player has food items
		bool actionSuccess = false;
		if (p.canAct()) {
			// Other players on the tile
			vector<Player> otherPlayers = bg.getPlayers(t);

			// Display tile action
			cout << t.getName() << endl;
			cout << t.getDescription() << endl;
			cout << endl;

			// If player chooses action
			cout << "Do action? 1 (True), 0 (false)" << endl;
			bool makeAction;
			cin >> makeAction;

			// Check if action is valid
			bool validAction = false;
			if (!t.actionValid(p, otherPlayers.size() - 1)){
				cout << "Cannot act on tile." << endl;
				cout << "Please press any key to continue" << endl;
				string placeholder;
				cin >> placeholder;
				validAction = false;
				//return false; // true
			} else {
				validAction = true;
			}

			if (makeAction && validAction) {
				// If tile has other players
				if (p.getGold() >= (int)otherPlayers.size()) {
					p.eat();
					for (auto op : otherPlayers) {
						// Player pays other players
						p.pay(op);
						bg.setPlayer(op);
					}
					// Perform action
					t.action(p);
					bg.setPlayer(p);
				}
				actionSuccess = true;
			}

			// Display player status
			cout << p << endl;
		}

		return actionSuccess;
	} catch (std::istream::failure e) {
		cout << "Incorrect key pressed";
		cin.clear();
	} catch (std::out_of_range e) {
		cout << e.what();
	}
	
	return false;
}

int main() {
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
			Tile * tile = tf->next();
			cout << "\n" << tile << endl;
			bg.add(*tile, i, j);
		}
	}

	// PLAY THE GAME //
	bg.setPlayers();

	// Iterate over players
	for (auto pName : playerNames) {
		do {
			cout << "====================================" << endl;
			cout << endl;
			cout << "Player " << pName << "'s turn" << endl;
			cout << endl;
		} while (! takeTurn<r>(bg, pName));
		// If player won
		if ( bg.win(pName) ) break;
	}
}