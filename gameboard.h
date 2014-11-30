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

#define PKEY
//#define PKEY_VEC
//#define TKEY
//#define TKEY_PTR
//#define TKEY_ADD

template<class T>
struct TileHashFunction {
#ifdef TKEY
	size_t operator() (const T& tile) const {
		//return std::hash<const T*>()(&tile);
		T t = tile;
		return std::hash<int>()(t.getId());
	}
#endif
#ifdef TKEY_PTR
	size_t operator() (const T* tile) const {
		return std::hash<const T*>()(&tile);
	}
#endif
};

template<class J>
struct PlayerHashFunction {
	size_t operator() (const J& player) const {
		J p = player;
		return std::hash<string>()(p.getName());
	}
};

template <class T, class J, const int R, const int C>
class GameBoard {
	// Vector of players
	vector<J> d_players;

	// 2D vector of tiles
#ifdef TKEY
	vector<vector<T>> d_tiles;
#else
	vector<vector<T*>> d_tiles;
#endif
#ifdef TKEY_ADD
	vector<vector<uint32>> d_tiles;
#endif

	// Map of <tile, players>
#ifdef TKEY
	unordered_map<T, vector<J>, TileHashFunction<T>> d_board;
#endif
#ifdef TKEY_PTR
	unordered_map<T*, vector<J>, TileHashFunction<T>> d_board;
#endif
#ifdef PKEY
	// This is less efficient than using T as keys
	// But it harder to hash over T since they have no
	// unique value
	// Tried with extern or random ID but failed
	// TODO ^ needs to be static not global/extern
#ifdef PKEY_VEC
	unordered_map<J, vector<int>, PlayerHashFunction<J>> d_board;
#else
	unordered_map<J, T*, PlayerHashFunction<J>> d_board;
#endif
#endif


public:
	enum Move {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	GameBoard();
	GameBoard(vector<J> _players) : d_players(_players) {};
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

	bool win(const string& playerName);

	const T& move(Move move, const string& playerName);

};

template <class T, class J, const int R, const int C>
GameBoard<T, J, R, C>::GameBoard() {

}

template <class T, class J, const int R, const int C>
GameBoard<T, J, R, C>::GameBoard(vector<string> _playerNames) {
	// Initialize players
	for (auto name : _playerNames) {
		J player = J(name);
		d_players.push_back(player);
#ifdef PKEY
#ifdef PKEY_VEC
		d_board[player] = vector<int>(2);
#else
		d_board[player] = new T();
#endif
#endif
	}

	// Initialize empty tile vector
	for (int i = 0; i < R; i++)	{
		for (int j = 0; j < C; j++)	{
#ifdef TKEY
			d_tiles.push_back(vector <T>());
			d_tiles[i].push_back(T());
#endif
#ifdef TKEY_PTR
			d_tiles.push_back(vector <T*>());
			d_tiles[i].push_back(new T());
#endif
#ifdef PKEY
			d_tiles.push_back(vector <T*>());
			d_tiles[i].push_back(new T());
#endif
		}
	}
}

template <class T, class J, const int R, const int C>
void GameBoard<T, J, R, C>::add(const T& tile, int row, int col){
	//std::cout << d_tiles[row][col] << std::endl;
#ifdef TKEY_PTR
	*d_tiles[row][col] = tile;
#endif
#ifdef TKEY
	d_tiles[row][col] = tile;
	d_board[tile];
#endif
#ifdef PKEY
	// The value in d_tiles is the address of the tile
	*d_tiles[row][col] = tile;
#endif
	cout << tile << "(" << &tile << ") - " << d_tiles[row][col] << " (" << d_tiles[row][col] << ")" << endl;

	//d_board[*tile];
	//d_board.insert(std::make_pair(&tile, vector<J>()));
	//d_board.addkey(tile);
}

#ifdef PKEY
template <class T, class J, const int R, const int C>
void GameBoard<T, J, R, C>::setPlayers() {
	auto baseTile = d_tiles[0][0];

	for (auto it = d_board.begin(); it != d_board.end(); ++it) {
		J player = it->first;
#ifdef PKEY_VEC
		d_board.insert(std::make_pair(player, vector<int>{0, 0}));
#else
		d_board.insert(std::make_pair(player, baseTile));
#endif
		cout << "Key = " << player.getName() << "\t" << "Val = " << baseTile << "(add " << &baseTile << ")" << endl;
	}
}
#else
template <class T, class J, const int R, const int C>
void GameBoard<T, J, R, C>::setPlayers() {
	auto baseTile = d_tiles[0][0];

	d_board.insert(std::make_pair(baseTile, d_players));
	///*
#ifdef TKEY
	T* address = &baseTile;
	cout << "BT address = " << address << endl;
	vector<J> plyrs = d_board[*address];
#endif
#ifdef TKEY_PTR
	vector<J> plyrs = d_board[baseTile];
#endif
	//*/
	for (auto it = d_board.begin(); it != d_board.end(); ++it) {
		cout << "Key: " << it->first << "\t" << (&(it->first)) << "\t";
		cout << "Val: ";
		for (auto p : it->second)
			cout << p.getName() << "\t";
		cout << endl;
	}
	cout << "==BBB==" << endl;

	cout << d_players.size() << endl; 
	cout << plyrs.size() << endl;
	//cout << d_board[&baseTile].size() << endl; 

	/*
	for (auto p : plyrs) {
		cout << "Name = " << p.getName() << endl;
	}
	//d_board.insert(make_pair(baseTile, d_players));
	//d_board[baseTile] = d_players;
	*/
}
#endif

template <class T, class J, const int R, const int C>
const T& GameBoard<T, J, R, C>::getTile(int row, int col) const{
	return *d_tiles[row][col];
}

template <class T, class J, const int R, const int C>
void GameBoard<T, J, R, C>::getCoordinate(const T &tile, int *row, int *col) const{
	for (int r = 0; r < R /*d_tiles.size()*/; r++) {
		for (int c = 0; c < C /*d_tiles[r].size()*/; c++) {
			if (*d_tiles[r][c] == tile) {
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

#ifdef PKEY
template <class T, class J, const int R, const int C>
J GameBoard<T, J, R, C>::getPlayer(const string& playerName){
	// Iterate over tiles
	for (auto player_iter = d_board.begin(); player_iter != d_board.end(); ++player_iter) {
		J player = player_iter->first;
		if (player.getName() == playerName) {
			return player;
		}
	}

	return NULL;
}
#else
template <class T, class J, const int R, const int C>
J GameBoard<T, J, R, C>::getPlayer(const string& playerName){
	// Iterate over tiles
	for (auto tile_iter = d_board.begin(); tile_iter != d_board.end(); ++tile_iter) {
		// Iterate over player vector
		for (auto player_iter = tile_iter->second.begin(); player_iter != tile_iter->second.end(); ++player_iter) {
			if (player_iter->getName() == playerName) {
				return *player_iter;
			}
		}
	}
	return NULL;
}
#endif

#ifdef PKEY
template <class T, class J, const int R, const int C>
const T& GameBoard<T, J, R, C>::getTile(const string& playerName) const{
	//T tile;
	// Iterate over tiles
	for (auto player_iter = d_board.begin(); player_iter != d_board.end(); ++player_iter) {
		J player = player_iter->first;
		if (player.getName() == playerName) {
			//tile = player_iter->second;
			//break;
#ifdef PKEY_VEC
			vector<int> vec = player_iter->second;
			cout << "[" << vec[0] << "," << vec[1] << "]" << endl;
			return *d_tiles[vec[0]][vec[1]];
#else
			cout << player_iter->second << endl;
			return *(player_iter->second);
#endif
		}
	}
	//return tile;
	return NULL;
}
#else
template <class T, class J, const int R, const int C>
const T& GameBoard<T, J, R, C>::getTile(const string& playerName) const{
	T tile;

	// Iterate over tiles
	for (auto tile_iter = d_board.begin(); tile_iter != d_board.end(); ++tile_iter) {
		// Iterate over player vector
		for (auto player_iter = tile_iter->second.begin(); player_iter != tile_iter->second.end(); ++player_iter) {
			J player = *player_iter;
			if (player.getName() == playerName) {
				tile = tile_iter->first;
			}
		}
	}

	return tile;
}
#endif

#ifdef PKEY
template <class T, class J, const int R, const int C>
vector<J> GameBoard<T, J, R, C>::getPlayers(const T& tile) const{
	vector<J> players;
	for (auto player_iter = d_board.begin(); player_iter != d_board.end(); ++player_iter) {
#ifdef PKEY_VEC
		vector<int> vec = player_iter->second;
		if (d_tiles[vec[0]][vec[1]] == tile) {
#else
		if (player_iter->second == tile) {
#endif
			J player = player_iter->first;
			players.push_back(player);
		}
	}
	return players
}
#else
template <class T, class J, const int R, const int C>
vector<J> GameBoard<T, J, R, C>::getPlayers(const T& tile) const{
	return d_board[tile];
}
#endif

#ifdef PKEY
template <class T, class J, const int R, const int C>
bool GameBoard<T, J, R, C>::win(const string& playerName){
	bool result = false;
	for (auto player_iter = d_board.begin(); player_iter != d_board.end(); ++player_iter) {
		J player = player_iter->first;
		if (player.getName() == playerName && player.getRuby() >= 5 ) {
			result = true;
			break;
		}
	}
	return result;
}
#else
template <class T, class J, const int R, const int C>
bool GameBoard<T, J, R, C>::win(const string& playerName){
	bool result = false;
	// Iterate over tiles
	for (auto tile_iter = d_board.begin(); tile_iter != d_board.end(); ++tile_iter) {
		// Iterate over player vector
		for (auto player_iter = tile_iter->second.begin(); player_iter != tile_iter->second.end(); ++player_iter) {
			if (player_iter->getName() == playerName && player_iter->getRuby() >= 5) {
				result = true;
				break;
			}
		}
	}
	return result;
}
#endif

template <class T, class J, const int R, const int C>
const T& GameBoard<T, J, R, C>::move(Move move, const string& playerName){
	// TODO make this more efficient

	// Find the tile player is on
	T old_tile = getTile(playerName);
	/*
	if (! old_tile==NULL ) {
		// Player not in board
		//return
	}
	*/
	int old_row = 0;
	int old_col = 0;
	getCoordinate(old_tile, &old_row, &old_col);

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
	T* new_tile = d_tiles[new_row][new_col];
	J player = getPlayer(playerName);
#ifdef PKEY
#ifdef PKEY_VEC
	d_board.insert(std::make_pair(player, vector<int>{new_row, new_col}));
#else
	d_board.insert(std::make_pair(player, new_tile));
#endif
#else
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
#endif
	cout << &new_tile << endl;
	int tmp_row = 0;
	int tmp_col = 0;
	getCoordinate(*new_tile, &tmp_row, &tmp_col);
	cout << tmp_row << ", " << tmp_col << endl;
	return *new_tile;
}
#endif