#include <iostream>
#include <map>
#include <vector>

using std::map;
using std::string;
using std::vector;

template <class T, class J, const int R, const int C>
class GameBoard {
	// TODO might not need this
	int d_numPlayers;
	vector<J> d_players;

	// TODO would be useful to use boost::multi_index's bidirectional map
	vector<vector<vector<J>>> d_tilesVec;
	// OR
	map<T, vector<J>> d_tilesMap;

	enum Move {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

public:
	GameBoard();

	GameBoard(vector<J> players);

	void add(const T& tile, int row, int col);

	const T& getTile(int row, int col) const;

	void getCoordinate(const T &tile, int *row, int *col) const;

	void setPlayer(J player);

	J getPlayer(const string& playerName);

	const T& getTile(const string& playerName) const;

	vector<J> getPlayers(const T& tile) const;

	const T& move(Move move, const string& playerName);
};