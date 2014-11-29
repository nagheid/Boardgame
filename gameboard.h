#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using std::map;
using std::string;
using std::unordered_map;
using std::vector;

template <class T, class J, const int R, const int C>
class GameBoard {
	// 2D vector of tiles
	vector<vector<T>> d_tiles[R][C];
	// Map of <tile, players>
	map<T, vector<J>> d_board;
	// OR
	//map<J, T> d_boardP;

	enum Move {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

public:
	GameBoard(vector<J> players);
	GameBoard(vector<string> playerNames);

	void add(const T& tile, int row, int col);

	const T& getTile(int row, int col) const;

	void getCoordinate(const T &tile, int *row, int *col) const;

	void setPlayer(J player);

	J getPlayer(const string& playerName);

	const T& getTile(const string& playerName) const;

	vector<J> getPlayers(const T& tile) const;

	const T& move(Move move, const string& playerName);

};