#include "gameboard.h"

template <class T, class J, const int R, const int C>
GameBoard<T,J,R,C>::GameBoard(const vector<J> _players){
	// initially, all players at tiles 0,0
	//if ( d_tiles.size() > 0 )
	// static_assert(d_tiles.size() > 0)
	T baseTile = d_tiles[0][0];
	d_board[baseTile] = _players;
}

template <class T, class J, const int R, const int C>
void GameBoard<T,J,R,C>::add(const T& tile, int row, int col){
	d_tiles[row][col] = tile;
}

template <class T, class J, const int R, const int C>
const T& GameBoard<T,J,R,C>::getTile(int row, int col) const{
	return d_tilesVec[row][col];
}

template <class T, class J, const int R, const int C>
void GameBoard<T,J,R,C>::getCoordinate(const T &tile, int *row, int *col) const{
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
void GameBoard<T,J,R,C>::setPlayer(J player){
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
J GameBoard<T,J,R,C>::getPlayer(const string& playerName){
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
const T& GameBoard<T,J,R,C>::getTile(const string& playerName) const{
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
vector<J> GameBoard<T,J,R,C>::getPlayers(const T& tile) const{
	return d_board[tile];
}

template <class T, class J, const int R, const int C>
const T& GameBoard<T,J,R,C>::move(Move move, const string& playerName){
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
