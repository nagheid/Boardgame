#include <stdio.h>
#include <string>
#include <sstream>

#include "gameboard.h"
#include "player.h"
#include "tile.h"

//const int R = 1;
//const int C = 1;

//#define GAMEBOARD_PARAM GameBoard<Tile, Player, R, C>

template <const int N>
bool takeTurn(GameBoard<Tile, Player, N, N> &bg, const std::string& pName) {
	// TODO
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
	std::cout << "1. no spaces between a player name, use '_'" << std::endl;
	std::cout << "2. use a space to separate more than one name\n" << std::endl;
	std::cout << "Please enter the player names separated by a space: " << std::endl;
	std::cout << "Enter an extra empty line when done" << std::endl;
	string line, name;
	//cin >> line;
	//while (getline(cin, line)) {
	getline(std::cin, line);
	istringstream streamLine(line);
	while (streamLine >> name) {
		//string name;
		//cin >> name;
		playerNames.push_back(name);
	}
	//}

	// Input the size of the board
	/*
	std::cout << "Please the number of rows in the board: " << std::endl;
	int rows; std::cin >> rows;
	std::cout << "Please the number of columns in the board: " << std::endl;
	int cols; std::cin >> cols;
	std::cout << "Please the number of rows and columms in the board: " << std::endl;
	int n; cin >> n;
	*/
	// Use a lamda
	/*const int N = []() -> int { 
								int r; 
								std::cin >> r; 
								return r; 
							  }();
							  */
	//const int N = in_get<int>();
	const int r = 6;
	const int c = 6;

	/*
	// Initialize a board game for N players
	// TODO why can't I pass N
	GameBoard<Tile, Player, r, c> bg(playerNames);

	// Initialize tiles
	TileFactory *tf = TileFactory::get(r*c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			bg.add(tf->next(), i, j);
		}
	}

	// Iterate over players
	for (auto pName : playerNames) {
		do {
			std::cout << pName; // bg.getPlayer(pName);
		} while (! takeTurn(bg, pName));
		//if ( bg.win(pName) ) break;
	}
	*/
}