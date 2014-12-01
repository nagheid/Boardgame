#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <cstdlib>
#include <functional>
#include <istream>
#include <iostream>
#include <map>
#include <ostream>
#include <unordered_map>
#include <vector>

using std::map;
using std::string;
using std::unordered_map;
using std::vector;
using std::istream;
using std::ostream;

#define PKEY
#define PKEY_VEC

template <class T, class J, const int R, const int C>
class GameBoard;
template <class T, class J, const int R, const int C>
inline ostream& operator<< (ostream&, const GameBoard<T,J,R,C> &);
template <class T, class J, const int R, const int C>
istream& operator>> (istream&, GameBoard<T, J, R, C> &);

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
	vector<vector<T*>> d_tiles;

	// Map of <tile, players>
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

	bool moveValid(Move move, const string& playerName);
	const T& move(Move move, const string& playerName);

	/*
	 * Overloading >> and << operators for save and load feature
	 */
	inline friend ostream& operator<<(ostream& os, const GameBoard& gameboard) {
		// TODO
		// Iterate over players
		for (auto player_iter = gameboard.d_board.begin(); player_iter != gameboard.d_board.end(); ++player_iter) {
			J player = player_iter->first;
#ifdef PKEY_VEC
			vector<int> vec = player_iter->second;
			T tile = *(gameboard.d_tiles[vec[0]][vec[1]]);
			T * tilePtr = gameboard.d_tiles[vec[0]][vec[1]];
#else
			T tile = *(player_iter->second);
#endif
			os << player;
			os << "Is on tile: ";
			os << tile << "\t(" << tilePtr /* << " - " << &tilePtr */ << ")" << endl;
		}
		return os;
	};

	friend istream& operator>>(istream& is, GameBoard& gameboard);

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
#ifdef PKEY
			d_tiles.push_back(vector <T*>());
			d_tiles[i].push_back(new T());
#endif
		}
	}
}

template <class T, class J, const int R, const int C>
void GameBoard<T, J, R, C>::add(const T& tile, int row, int col){
	// The value in d_tiles is the address of the tile
	*d_tiles[row][col] = tile;
	T * tilePtr = d_tiles[row][col];
	cout << tile << "\t(" << tilePtr /* << /* " - " << &tilePtr */ << ")" << endl;
}

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
	}
}

template <class T, class J, const int R, const int C>
const T& GameBoard<T, J, R, C>::getTile(int row, int col) const{
	return *d_tiles[row][col];
}

template <class T, class J, const int R, const int C>
void GameBoard<T, J, R, C>::getCoordinate(const T &tile, int *row, int *col) const{
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			if (*d_tiles[r][c] == tile) {
				*row = r;
				*col = c;
				return;
			}
		}
	}
}

template <class T, class J, const int R, const int C>
void GameBoard<T, J, R, C>::setPlayer(J player){
	// Iterate over players
	for (auto player_iter = d_board.begin(); player_iter != d_board.end(); ) {
		J p = player_iter->first;
		// If found player
		if (p.getName() == player.getName()) {
			// Update pointer
#ifdef PKEY
#ifdef PKEY_VEC
			vector<int> tiles = player_iter->second;
#else
			T* tiles = player_iter->second;
#endif
#endif
			d_board.erase(player_iter);
			d_board[player] = tiles;
			//*(player_iter->first) = &player;
			break;
		} else {
			player_iter++;
		}
	}
}

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

template <class T, class J, const int R, const int C>
const T& GameBoard<T, J, R, C>::getTile(const string& playerName) const{
	// Iterate over players
	for (auto player_iter = d_board.begin(); player_iter != d_board.end(); ++player_iter) {
		J player = player_iter->first;
		if (player.getName() == playerName) {
#ifdef PKEY_VEC
			vector<int> vec = player_iter->second;
			return *d_tiles[vec[0]][vec[1]];
#else
			return *(player_iter->second);
#endif
		}
	}
	//return tile;
	return NULL;
}

template <class T, class J, const int R, const int C>
vector<J> GameBoard<T, J, R, C>::getPlayers(const T& tile) const{
	int tmp_row = 0;
	int tmp_col = 0;
	getCoordinate(tile, &tmp_row, &tmp_col);
	
	vector<J> players;
	for (auto player_iter = d_board.begin(); player_iter != d_board.end(); ++player_iter) {
#ifdef PKEY_VEC
		vector<int> vec = player_iter->second;
		if (*d_tiles[vec[0]][vec[1]] == tile) {
#else
		T t = *(player_iter->second);
		if (t == tile) {
#endif
			J player = player_iter->first;
			players.push_back(player);
		}
	}
	return players;
}

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

template <class T, class J, const int R, const int C>
bool GameBoard<T, J, R, C>::moveValid(Move move, const string& playerName){
	// TODO 
	return true;
}

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
	d_board[player] = vector<int>{new_row, new_col};
#else
	d_board[player] = new_tile;
#endif
#endif
	int tmp_row = 0;
	int tmp_col = 0;
	getCoordinate(*new_tile, &tmp_row, &tmp_col);
	return *new_tile;
}


template <class T, class J, const int R, const int C>
inline ostream& operator<<(ostream& os, const GameBoard<T, J, R, C>& gameboard) {
	// TODO
	// Iterate over players
	for (auto player_iter = gameboard.d_board.begin(); player_iter != gameboard.d_board.end(); ++player_iter) {
		J player = player_iter->first;
#ifdef PKEY_VEC
		vector<int> vec = player_iter->second;
		T tile = *(gameboard.d_tiles[vec[0]][vec[1]]);
#else
		T tile = *(player_iter->second);
#endif
		os << player << endl;
		os << " is on tile: ";
		os << tile;
	}
	return os;
}

template <class T, class J, const int R, const int C>
istream& operator>>(istream& is, GameBoard<T, J, R, C>& gameboard) {
	// TODO
	return is;
}

#endif