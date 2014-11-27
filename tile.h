#include <iostream>
#include <vector>
#include "player.h"

using namespace std;

class Tile {
public:
	bool operator==(const Tile &t);
	virtual bool action(Player& player);
	virtual Tile* clone();
	ostream& operator<<(ostream& os);
};

class RestaurantTile : public Tile {
public:
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class SpiceMerchantTile : public Tile {
public:
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class FabricManufacturesTile : public Tile {
public:
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class JewelerTile : public Tile {
public:
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class CartManufacturerTile : public Tile {
public:
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class SmallMarketTile : public Tile {
public:
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class SpiceMarketTile : public Tile {
public:
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class JelewryMarketTile : public Tile {
public:
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class FabricMarketTile : public Tile {
public:
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class BlackMarketTile : public Tile {
public:
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class CasinoTile : public Tile {
public:
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class GemMerchantTile : public Tile {
private:
	int sold;
public:
	GemMerchantTile(int _sold = 0);
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class PalaceTile : public Tile {
public:
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
