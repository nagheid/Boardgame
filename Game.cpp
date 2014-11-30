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
		cout << p.getName() << endl;
		cout << "Food: " << p.getFood() << endl;
		cout << "Gold: " << p.getGold() << endl;
		cout << "Fabric: " << p.getFabric() << endl;
		cout << "Spices: " << p.getSpice() << endl;
		cout << "Jeweles: " << p.getJewel() << endl;
		cout << "Rubies: " << p.getRuby() << endl;
		cout << "Space in cart: " << p.getCart() - p.totalGoods() << endl;
		cout << endl;

		// Input move
		//GameBoard<Tile, Player, N, N>::Move m = GameBoard<Tile, Player, N, N>::DOWN;
		cout << "Please enter one of the following values:" << endl;
		cout << "0(UP), 1(DOWN), 2(LEFT), 3(RIGHT)" << endl;
		cin.exceptions(std::istream::failbit); 
		int intM; cin >> intM;

		// TODO there must be a better way
		std::map<int, GameBoard<Tile, Player, N, N>::Move> map;
		map[0] = GameBoard<Tile, Player, N, N>::UP;
		map[1] = GameBoard<Tile, Player, N, N>::DOWN;
		map[2] = GameBoard<Tile, Player, N, N>::LEFT;
		map[3] = GameBoard<Tile, Player, N, N>::RIGHT;

		GameBoard<Tile, Player, N, N>::Move m = map[intM];
		cout << "Move = " << m << endl;

		// Move player to tile
		const Tile t = bg.move(m, pName);
		cout << "Returned tile : " << t << " (" << &t << ")" << endl;

		Tile tl = bg.getTile(pName);
		cout << "Get tile : " << tl << " (" << &tl << ")" << endl;

		// If player has food items
		if (p.canAct()) {
			// TODO display tile action

			// If player chooses action
			bool makeAction;
			cin >> makeAction;
			if (makeAction) {
				// TODO check if action is valid

				// If tile has other players
				vector<Player> opL = bg.getPlayers(t);
				if (p.getGold() >= (int)opL.size()) {
					p.eat();
					for (auto op : opL) {
						// Player pays other players
						p.pay(op);
						bg.setPlayer(op);
					}
					// Perform action
					// TODO uncomment when fix 'action' error
					//t.action(p);
					bg.setPlayer(p);
				}
			}

			// TODO display player status
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
			//Player player = bg.getPlayer(pName);
			cout << pName << endl;
		} while (! takeTurn<r>(bg, pName));
		// If player won
		if ( bg.win(pName) ) break;
	}
}