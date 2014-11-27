#include "gameboard.h"

template <class T, class P, const int R, const int C>
GameBoard(const T& tile, int row, int col){

}

template <class T, class P, const int R, const int C>
void GameBoard::add(const T& tile, int row, int col){
	d_tilesVec[row][col] = tile;
}

template <class T, class P, const int R, const int C>
const T& getTile(int row, int col) const{
	return d_tilesVec[row][col];
}

template <class T, class P, const int R, const int C>
void getCoordinate(const T &tile, int *row, int *col) const{

}

template <class T, class P, const int R, const int C>
void setPlayer(J player){

}

template <class T, class P, const int R, const int C>
J getPlayer(const string& playerName){

}

template <class T, class P, const int R, const int C>
const T& getTile(const string& playerName) const{

}

template <class T, class P, const int R, const int C>
vector<J> getPlayers(const T& tile) const{

}

template <class T, class P, const int R, const int C>
const T& move(Enum Move move, const string& playerName){

}
