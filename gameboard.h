#include <iostream>

template <class T, class P, const int N>
class GameBoard {
public:
	void add(const T& tile, int row, int col);
	const T& getTile(int row, int col) const;
	void getCoordinate(const T &tile, int *row, int *col) const;
	void setPlayer(J player);
	J getPlayer(const std::string& playerName);
	const T& getTile(const std::string& playerName) const;
	std::vector<J> getPlayers(const T& tile) const;
	const T& move(Enum Move move, const std::string& playerName);
};