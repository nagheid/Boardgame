#include <iostream>
#include "player.h"

using namespace std;

class Tile {
public:
	bool operator==(const Tile &t);
	virtual bool action(Player& player);
	virtual Tile* clone();
	ostream& operator<<(ostream& os);
};

class TileFactory {
public:
	TileFactory(int numOfTiles);
	Tile* next();
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
public:
	virtual bool action(Player& player);
	virtual Tile* clone();
};

class PalaceTile : public Tile {
public:
	virtual bool action(Player& player);
	virtual Tile* clone();
};
