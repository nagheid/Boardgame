#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include "tile.h"

using std::map;
using std::string;
using std::unordered_map;
using std::vector;

/*
template<>
struct std::hash<Tile>
{
	size_t operator()(const Tile& obj) const
	{
		return std::hash<const Tile*>()(&obj);
	}
};
//*/
//*
template<class T>
struct BoardHashFunction {
	size_t operator() (const T& tile) const {
		return std::hash<const T*>()(&tile);
		//return std::hash<int>(rand() % 100 + 1);
		//return std::hash<int>(tile->id); 
	}
};
//*/

template <class T, class J, const int R, const int C>
class GameBoard {
	// Vector of players
	vector<J> d_players;

	// 2D vector of tiles
	vector<vector<T>> d_tiles;

	// Map of <tile, players>
	unordered_map<T, vector<J>, BoardHashFunction<T>> d_board;
	//map<T, vector<J>> d_board;

	enum Move {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

public:
	GameBoard();
	GameBoard(vector<J> _players);
	GameBoard(vector<string> _playerNames);

	void add(const T& tile, int row, int col);

	const T& getTile(int row, int col) const;

	void getCoordinate(const T &tile, int *row, int *col) const;

	void setPlayer(J player);

	J getPlayer(const string& playerName);

	const T& getTile(const string& playerName) const;

	vector<J> getPlayers(const T& tile) const;

	void setPlayers();
	void setPlayers(vector<string> _playerNames);

	const T& move(Move move, const string& playerName);

};

template <class T, class J, const int R, const int C>
GameBoard<T, J, R, C>::GameBoard() {

}

template <class T, class J, const int R, const int C>
GameBoard<T, J, R, C>::GameBoard(const vector<J> _players){
	T baseTile = d_tiles[0][0];
	//d_board[baseTile] = _players;
}

template <class T, class J, const int R, const int C>
GameBoard<T, J, R, C>::GameBoard(vector<string> _playerNames) {
	// Initialize players
	for (auto name : _playerNames) {
		d_players.push_back(J(name));
	}
	cout << _playerNames.size() << endl;
	cout << d_players.size() << endl;

	// Initialize empty tile vector
	for (int i = 0; i < R; i++)	{
		for (int j = 0; j < C; j++)	{
			d_tiles.push_back(vector <T>());
			d_tiles[i].push_back(T());
		}
	}

	// Initialize empty board
}

/*
template <class T, class J, const int R, const int C>
void GameBoard<T, J, R, C>::setPlayers(vector<string> _playerNames){
	for (auto name : _playerNames) {
		d_players.push_back(J(name));
	}

	T baseTile = d_tiles[0][0];
	d_board[baseTile] = d_players;
}
*/

template <class T, class J, const int R, const int C>
void GameBoard<T, J, R, C>::setPlayers() {
	auto baseTile = d_tiles[0][0];
	d_board[baseTile] = d_players;
	//d_board.insert(std::make_pair(baseTile, d_players));

	vector<J> plyrs = d_board[baseTile];
	
	cout << d_players.size() << endl; 
	cout << plyrs.size() << endl;
	cout << d_board[baseTile].size() << endl; 

	for (auto p : plyrs) {
		cout << "Name = " << p.getName() << endl;
	}
	//d_board.insert(make_pair(baseTile, d_players));
	//d_board[baseTile] = d_players;
}

template <class T, class J, const int R, const int C>
void GameBoard<T, J, R, C>::add(const T& tile, int row, int col){
	//std::cout << d_tiles[row][col] << std::endl;
	d_tiles[row][col] = tile;
	cout << &tile << " - " << &d_tiles[row][col] << endl;

	//d_board[tile] = vector<J>();
	//d_board.insert(std::make_pair<T, vector<J>>(tile, vector<J>()));
	//d_board.addkey(tile);
}

template <class T, class J, const int R, const int C>
const T& GameBoard<T, J, R, C>::getTile(int row, int col) const{
	return d_tilesVec[row][col];
}

template <class T, class J, const int R, const int C>
void GameBoard<T, J, R, C>::getCoordinate(const T &tile, int *row, int *col) const{
	for (int r = 0; r < R /*d_tiles.size()*/; r++) {
		for (int c = 0; c < C /*d_tiles[r].size()*/; c++) {
			if (d_tiles[r][c] == tile) {
				// TODO test that this is copied correctly;
				*row = r;
				*col = c;
			}
		}
	}
}

template <class T, class J, const int R, const int C>
void GameBoard<T, J, R, C>::setPlayer(J player){
	// Iterate over map
	for (auto tile_iter = d_board.begin(); tile_iter != d_board.end(); ++tile_iter) {
		// Iterate over player vector
		for (auto player_iter = tile_iter->second.begin(); player_iter != tile_iter->second.end(); ++player_iter) {
			// If found player
			if (player_iter->getName() == player.getName()) {
				// Update pointer
				*player_iter = player;
			}
		}
	}
}

template <class T, class J, const int R, const int C>
J GameBoard<T, J, R, C>::getPlayer(const string& playerName){
	J player;

	// Iterate over tiles
	for (auto tile_iter = d_board.begin(); tile_iter != d_board.end(); ++tile_iter) {
		// Iterate over player vector
		for (auto player_iter = tile_iter->second.begin(); player_iter != tile_iter->second.end(); ++player_iter) {
			if (player_iter->getName() == playerName) {
				player = *player_iter;
			}
		}
	}

	return player;
}

template <class T, class J, const int R, const int C>
const T& GameBoard<T, J, R, C>::getTile(const string& playerName) const{
	T tile;

	// Iterate over tiles
	for (auto tile_iter = d_board.begin(); tile_iter != d_board.end(); ++tile_iter) {
		// Iterate over player vector
		for (auto player_iter = tile_iter->second.begin(); player_iter != tile_iter->second.end(); ++player_iter) {
			if (player_iter->getName() == playerName) {
				tile = tile_iter->first;
			}
		}
	}

	return tile;
}

template <class T, class J, const int R, const int C>
vector<J> GameBoard<T, J, R, C>::getPlayers(const T& tile) const{
	return d_board[tile];
}

template <class T, class J, const int R, const int C>
const T& GameBoard<T, J, R, C>::move(Move move, const string& playerName){
	// TODO make this more efficient

	// Find the tile player is on
	T old_tile = getTile(playerName);
	if (!old_tile) {
		// Player not in board
		//return
	}
	int old_row = 0;
	int old_col = 0;
	getCoordinate(old_tile, *old_row, *old_col);

	// Figure out which tile to move player to
	int new_row = 0;
	int new_col = 0;
	//newCoordinate(move, *old_row, *old_col, *new_row, *new_col);
	switch (move) {
	case UP:
		new_row = (old_row - 1) % R;
		new_col = old_col;
		break;
	case DOWN:
		new_row = (old_row + 1) % R;
		new_col = old_col;
		break;
	case RIGHT:
		new_row = old_row;
		new_col = (old_col + 1) % C;
		break;
	case LEFT:
		new_row = old_row;
		new_col = (old_col - 1) % C;
		break;
	}

	// Move the player to new tile
	T new_tile = d_tiles[new_row][new_col];
	J player = getPlayer(playerName);
	// Iterate over tiles
	for (auto tile_iter = d_board.begin(); tile_iter != d_board.end(); ++tile_iter) {
		// Iterate over player vector
		if (tile_iter->first == old_tile) {
			for (auto player_iter = tile_iter->second.begin(); player_iter != tile_iter->second.end(); ++player_iter) {
				if (player_iter->getName() == playerName) {
					tile_iter->second.erase(player_iter);
				}
			}
		}

		if (tile_iter->first == new_tile) {
			tile_iter->second.push_back(player);
		}
	}
}

#endif