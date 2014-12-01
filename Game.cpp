#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <istream>
#include <iostream>
#include <vector>
#include <map>

#include "gameboard.h"
#include "player.h"
#include "tile.h"

using std::cerr;

// ----------------------------------------------------------------------------
// save
// ----------------------------------------------------------------------------
template <const int N>
void save(GameBoard<Tile, Player, N, N> &bg) {
	ofstream ofs("boardgame.txt", ios::binary);
	//ofs.write((char *)bg, sizeof(bg));
	ofs << bg;
	ofs.close();
}

// ----------------------------------------------------------------------------
// load
// ----------------------------------------------------------------------------
template <const int N>
bool load(GameBoard<Tile, Player, N, N> &bg) {
	ifstream ifs("boardgame.txt", ios::binary);

	if (ifs) {
		/*
		string str;		getline(ifs, str, '|');
		std::istringstream ss(str);
		ss >> bg;
		*/
		ifs >> bg;
		cout << bg;
		return true;
	} else {
		return false;
	}
} 

// ----------------------------------------------------------------------------
// takeTurn
// ----------------------------------------------------------------------------
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
		Tile& old_tile = (Tile&)bg.getTile(pName);
		cout << "Player is on tile:\t" << old_tile << endl;

		// Check if move is valid
		if (!bg.moveValid(m, pName)) {
			cerr << "Invalid move!" << endl;
			return false;
		}


		// Move player to tile
		Tile& t = (Tile&)bg.move(m, pName);
		cout << "Player moved to tile:\t" << t << endl;

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

template <const int N>
void setup(GameBoard<Tile, Player, N, N> &bg) {
	// SETUP THE BOARD //

	// Input the names of all players
	vector<string> playerNames;
	cout << endl;
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

	// Initialize a board game
	//bg = GameBoard<Tile, Player, N, N>(playerNames);

	// Initialize tiles
	cout << "The board contains the following tiles:" << endl;
	TileFactory *tf = TileFactory::get(N*N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Tile * tile = tf->next();
			bg.add(*tile, i, j);
		}
	}

	bg.setPlayers(playerNames);
}

// ----------------------------------------------------------------------------
// main
// ----------------------------------------------------------------------------
int main() {
	// The size of the board
	const int N = 6;

	// LOAD //
	cout << "Would you like to resume a game? 1 (YES), 0 (NO)" << endl;
	bool resume = false;
	cin >> resume;

	// Empty cin buffer
	string line; getline(cin, line);

	GameBoard<Tile, Player, N, N> bg;
	if (resume) {
		bool loaded = load<N>(bg);
		if (loaded) {
			cout << "Game loaded successfully\n" << endl;
		} else {
			cout << "There is nothing to load" << endl;
			cout << "Will set up a new game\n" << endl;
			setup<N>(bg);
		}
	} else {
		setup<N>(bg);
	}

	vector<string> playerNames = bg.getPlayerNames();

	// PLAY THE GAME //
	bool isWinner = false;

	while (!isWinner){
		// Check if player wants to pause 
		cout << "Would you like to pause the game? 1 (YES), 0 (NO)" << endl;
		bool pause = false;	cin >> pause;
		// Empty cin buffer
		getline(cin, line);
		// Save
		if (pause) {
			save<N>(bg);
			return 0;
		}

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
			while (! takeTurn<N>(bg, pName));

			// If player won
			if (bg.win(pName)){
				cout << pName << " WINS!" << endl;
				isWinner = true;
				break;
			}
		}
	}

	return 0;
}