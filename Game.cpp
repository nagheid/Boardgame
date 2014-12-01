#include <stdio.h>
#include <string>
#include <sstream>
#include <istream>
#include <iostream>
#include <vector>

#include "gameboard.h"
#include "player.h"
#include "tile.h"

using std::cerr;

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

		// Get current tile
		Tile& t = (Tile&)bg.getTile(pName);
		cout << "Player is on tile:\t" << t << endl;

		// Check if move is valid
		if (bg.moveValid(m, pName)) {
			// Move player to tile
			t = (Tile&)bg.move(m, pName);
			cout << "Player moved to tile:\t" << t << endl;
		} else {
			cerr << "Invalid move!" << endl;
			return false;
		}

		// If player has food items
		if (p.canAct()) {
			// Other players on the tile
			vector<Player> otherPlayers = bg.getPlayers(t);

			// Display tile action
			cout << t.getName() << endl;
			cout << t.getDescription() << endl;
			cout << endl;

			// Check if action is valid
			bool validAction = false;
			bool makeAction = false;

			if (! t.actionValid(p, otherPlayers.size() - 1)){
				cerr << "Cannot act on tile." << endl;
				system("pause");
				validAction = false;
				//return false; // true
			}
			else {
				validAction = true;

				// If player chooses action
				cout << "Do action? 1 (YES), 0 (NO)" << endl;
				
				cin >> makeAction;
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
					cout << endl;
					t.action(p);
					bg.setPlayer(p);
				}
			}

			// Display player status
			cout << p << endl;
		}
		cout << p.getName() << "'s turn is over." << endl;
		system("pause");
		return true;
	} catch (std::istream::failure e) {
		cerr << "Incorrect key pressed" << endl;
		cin.clear();
	} catch (std::out_of_range e) {
		cerr << e.what() << endl;
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
	cout << "The board contains the following tiles:" << endl;
	TileFactory *tf = TileFactory::get(r*c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			Tile * tile = tf->next();
			bg.add(*tile, i, j);
		}
	}

	// PLAY THE GAME //
	bg.setPlayers();

	bool isWinner = false;

	while (!isWinner){
		// Iterate over players
		for (auto pName : playerNames) {
			do {
				cout << endl; 
				cout << "====================================" << endl;
				cout << bg << endl;
				cout << endl;
				cout << "Player " << pName << "'s turn" << endl;
				cout << endl;
			}	// Keep playing if takeTurn returns false
			while (! takeTurn<r>(bg, pName));
			// If player won
			if (bg.win(pName)){
				cout << pName << " WINS!" << endl;
				isWinner = true;
				break;
			}
		}
	}
}