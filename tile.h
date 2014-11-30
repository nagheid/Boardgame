#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include "player.h"

using namespace std;

class Tile;
istream& operator>>(istream&, Tile&);
ostream& operator<<(ostream&, const Tile&);

class Tile {
protected:
	int id;
	int actionCount;
public:
	Tile(int actionCount = 0);
	bool operator==(const Tile &t) const;
	virtual bool action(Player& player);
	virtual Tile* clone();

	int getActionCount(){ return actionCount; }
	int getId(){ return id; }

	friend ostream& operator<<(ostream& os, const Tile& tile);
	friend istream& operator>>(istream& is, Tile& tile);
};

class RestaurantTile : public Tile {
public:
	RestaurantTile(int actionCount = 0);
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class SpiceMerchantTile : public Tile {
public:
	SpiceMerchantTile(int actionCount = 0);
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class FabricManufacturesTile : public Tile {
public:
	FabricManufacturesTile(int actionCount = 0);
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class JewelerTile : public Tile {
public:
	JewelerTile(int actionCount = 0);
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class CartManufacturerTile : public Tile {
public:
	CartManufacturerTile(int actionCount = 0);
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class SmallMarketTile : public Tile {
public:
	SmallMarketTile(int actionCount = 0);
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class SpiceMarketTile : public Tile {
public:
	SpiceMarketTile(int actionCount = 0);
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class JelewryMarketTile : public Tile {
public:
	JelewryMarketTile(int actionCount = 0);
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class FabricMarketTile : public Tile {
public:
	FabricMarketTile(int actionCount = 0);
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class BlackMarketTile : public Tile {
public:
	BlackMarketTile(int actionCount = 0);
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class CasinoTile : public Tile {
public:
	CasinoTile(int actionCount = 0);
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class GemMerchantTile : public Tile {
public:
	GemMerchantTile(int actionCount = 0);
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class PalaceTile : public Tile {
public:
	PalaceTile(int actionCount = 0);
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class TileFactory {
private:
	static TileFactory* instance;
	int nTiles;
	int max;
	vector<Tile> tiles;
	TileFactory(int _nTiles);
	TileFactory(TileFactory const&) {};
	TileFactory& operator=(TileFactory const&){};

public:
	static TileFactory* get(int _nTiles);
	Tile* next();
};

#endif