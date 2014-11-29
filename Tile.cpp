#include "tile.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// ----------------------------------------------------------------------------
// Desert (Default Tile)
// No action is possible on this tile. This is the base class behaviour
// ----------------------------------------------------------------------------

Tile::Tile(int _actionCount=0) : actionCount(_actionCount) {}

bool Tile::operator==(const Tile &t){
	return this == &t;
}

bool Tile::action(Player& player){
	actionCount++;
	return true;
}

Tile* Tile::clone(){
	return new Tile(getActionCount());
}

ostream& Tile::operator<<(ostream& os){
	return os << actionCount;
}

istream& operator>>(istream& is, Tile& tile){
	is >> tile.actionCount;
	return is;
}


// ----------------------------------------------------------------------------
// Restaurant
// The number of food items of a player is replenished and will be set to 10.
// This is the initial position of all players.
// ----------------------------------------------------------------------------

RestaurantTile::RestaurantTile(int _actionCount) : Tile(_actionCount) {}

bool RestaurantTile::action(Player& player){
    player.setFood(10);
    return true;
}

Tile* RestaurantTile::clone(){
	return &RestaurantTile();
}

// ----------------------------------------------------------------------------
// Spice Merchant
// For 2 pieces of gold, a player can purchase 3 sacks of spices (less if the
// player does not have a capacity in his / her cart).
// ----------------------------------------------------------------------------

SpiceMerchantTile::SpiceMerchantTile(int _actionCount=0) : Tile(_actionCount) {}

bool SpiceMerchantTile::action(Player& player){
	int space = player.getCart() - player.totalGoods();
    if(player.getGold() >= 2 && space > 0){
        player.setGold(player.getGold() - 2);
        if(space < 3){
			player.setSpice(player.getSpice() + space);
        }
        else{
            player.setSpice(player.getSpice() + 3);
        }
        return true;
    }
    return false;
}

Tile* SpiceMerchantTile::clone(){
	return new SpiceMerchantTile(getActionCount());
}


// ----------------------------------------------------------------------------
// Fabric Manufactures
// For 2 pieces of gold, the player gets three rolls of fabrics tissues
// (less if the player does not have a capacity in his / her cart)
// ----------------------------------------------------------------------------

FabricManufacturesTile::FabricManufacturesTile(int _actionCount=0) : Tile(_actionCount) {}

bool FabricManufacturesTile::action(Player& player){
	int space = player.getCart() - player.totalGoods();
    if(player.getGold() >= 2 && space > 0){
        player.setGold(player.getGold() - 2);
        if(space < 3){
			player.setFabric(player.getFabric() + space);
        }
        else{
            player.setFabric(player.getFabric() + 3);
        }
        return true;
    }
    return false;
}

Tile* FabricManufacturesTile::clone(){
	return new FabricManufacturesTile(getActionCount());
}


// ----------------------------------------------------------------------------
// Jeweler
// For 2 pieces of gold, the player gets 3 pieces of jewelry (less if the
// player does not have a capacity in his cart).
// ----------------------------------------------------------------------------

JewelerTile::JewelerTile(int _actionCount-0) : Tile(_actionCount) {}

bool JewelerTile::action(Player& player){
	int space = player.getCart() - player.totalGoods();
    if(player.getGold() >= 2 && space > 0){
        player.setGold(player.getGold() - 2);
        if(space < 3){
			player.setJewel(player.getJewel() + space);
        }
        else{
            player.setJewel(player.getJewel() + 3);
        }
        return true;
    }
    return false;
}

Tile* JewelerTile::clone(){
	return new JewelerTile(getActionCount());
}


// ----------------------------------------------------------------------------
// Cart Manufacturer
// For 7 pieces of gold, the capacity of the cart is increased by 3.
// ----------------------------------------------------------------------------

CartManufacturerTile::CartManufacturerTile(int _actionCount=0) : Tile(_actionCount) {}

bool CartManufacturerTile::action(Player& player){
    if(player.getGold() >= 7){
        player.setGold(player.getGold() - 7);
        player.setCart(player.getCart() + 3);
        return true;
    }
    return false;
}

Tile* CartManufacturerTile::clone(){
	return new CartManufacturerTile(getActionCount());
}


// ----------------------------------------------------------------------------
// Small Market
// A player can sell 1 roll of fabric, 1 jewel and 1 sack of spices for 8
// pieces of gold.
// ----------------------------------------------------------------------------

SmallMarketTile::SmallMarketTile(int _actionCount=0) : Tile(_actionCount) {}

bool SmallMarketTile::action(Player& player){
    if(player.getFabric() > 0 && player.getJewel() > 0 && player.getFabric() > 0){
        player.setFabric(player.getFabric() - 1);
        player.setJewel(player.getJewel() - 1);
        player.setFabric(player.getFabric() -1);
        player.setGold(player.getGold() + 8);
        return true;
    }
    return false;
}

Tile* SmallMarketTile::clone(){
	return new SmallMarketTile(getActionCount());
}

// ----------------------------------------------------------------------------
// Spice Market
// A player can sell 3 sacks of spices for 6 pieces of gold.
// ----------------------------------------------------------------------------

SpiceMarketTile::SpiceMarketTile(int _actionCount=0) : Tile(_actionCount) {}

bool SpiceMarketTile::action(Player& player){
    if(player.getSpice() >= 3){
        player.setSpice(player.getSpice() - 3);
        player.setGold(player.getGold() + 6);
		return true;
    }
	return false;
}

Tile* SpiceMarketTile::clone(){
	return new SpiceMarketTile(getActionCount());
}


// ----------------------------------------------------------------------------
// Jelewry Market
// A player can sell 3 pieces of jewelry for 6 pieces of gold.
// ----------------------------------------------------------------------------

JelewryMarketTile::JelewryMarketTile(int _actionCount=0) : Tile(_actionCount) {}

bool JelewryMarketTile::action(Player& player){
    if(player.getJewel() >= 3){
        player.setJewel(player.getJewel() - 3);
        player.setGold(player.getGold() + 6);
		return true;
    }
	return false;
}

Tile* JelewryMarketTile::clone(){
	return new JelewryMarketTile(getActionCount());
}


// ----------------------------------------------------------------------------
// Fabric Market
// A player can sell 3 rolls of fabrics for 6 pieces of gold.
// ----------------------------------------------------------------------------

FabricMarketTile::FabricMarketTile(int _actionCount=0) : Tile(_actionCount) {}

bool FabricMarketTile::action(Player& player){
    if(player.getFabric() >= 3){
        player.setFabric(player.getFabric() - 3);
        player.setGold(player.getGold() + 6);
		return true;
    }
	return false;
}

Tile* FabricMarketTile::clone(){
	return new FabricMarketTile(getActionCount());
}

// ----------------------------------------------------------------------------
// Black Market
// For 1 piece of gold, a player can get between 0 and 5 goods at random (less
// if the player does not have a capacity in his / her cart).
// ----------------------------------------------------------------------------

BlackMarketTile::BlackMarketTile(int _actionCount=0) : Tile(_actionCount) {}

bool BlackMarketTile::action(Player& player){

	int numOfItems = rand() % 6;
	int space = player.getCart() - player.totalGoods();

	if (space < numOfItems){
		numOfItems = space;
	}

	for (int i = 0; i < numOfItems; i++){
		int tileNum = rand() % 4 + 1;
		if (tileNum == 1){
			player.setSpice(player.getSpice() + 1);
		}
		else if (tileNum == 2){
			player.setFabric(player.getFabric() + 1);
		}
		else if (tileNum == 3){
			player.setJewel(player.getJewel() + 1);
		}
		else if (tileNum == 4){
			player.setRuby(player.getRuby() + 1);
		}
	}

	return true;
}

Tile* BlackMarketTile::clone(){
	return new BlackMarketTile(getActionCount());
}


// ----------------------------------------------------------------------------
// Casino
// For 1 piece of gold, the player has 2 in 5 chance to loose, i.e., win 0
// pieces of gold, a 3 out of 10 chance to get 2 pieces of gold, a 2 out of 10
// chance to get 3 pieces of gold and a 1 in 10 chance to win 10 pieces of
// gold.
// ----------------------------------------------------------------------------

CasinoTile::CasinoTile(int _actionCount=0) : Tile(_actionCount) {}

bool CasinoTile::action(Player& player){
	if (player.getGold() < 1){
		return false;
	}

	int num = rand() % 10 + 1;

	if (num == 1){
		player.setGold(player.getGold() + 10);
	}
	else if (num > 1 && num < 4){
		player.setGold(player.getGold() + 3);
	}
	else if (num > 3 && num < 7){
		player.setGold(player.getGold() + 2);
	}

	return true;
}

Tile* CasinoTile::clone(){
	return new CasinoTile(getActionCount());
}

// ----------------------------------------------------------------------------
// Gem Merchant
// A player can buy a ruby. The first ruby costs 12 gold coins, the second ruby
// to be purchased costs 13, the third 14, etc.
// ----------------------------------------------------------------------------

GemMerchantTile::GemMerchantTile(int _actionCount=0) : Tile(_actionCount) {}

bool GemMerchantTile::action(Player& player) {
	int nextSellPrice = 12 + getActionCount();
	if (player.getGold() >= nextSellPrice){
		player.setGold(player.getGold() - nextSellPrice);
		player.setRuby(player.getRuby() + 1);
		Tile::action(player);
		return true;
	}
	return false;
}

Tile* GemMerchantTile::clone(){
	return new GemMerchantTile(getActionCount());
}

// ----------------------------------------------------------------------------
// Palace
// A player can get a ruby in exchange for 5 rolls of fabrics, 5 pieces of
// jewelry and 5 sacks of spices.
// ----------------------------------------------------------------------------

PalaceTile::PalaceTile(int _actionCount=0) : Tile(_actionCount) {}

bool PalaceTile::action(Player& player){
	if (player.getFabric() >= 5 && player.getJewel() >= 5 && player.getSpice() >= 5){
		player.setFabric(player.getFabric() - 5);
		player.setJewel(player.getJewel() - 5);
		player.setSpice(player.getSpice() - 5);
		player.setRuby(player.getRuby() + 1);
		return true;
	}
	return false;
}

Tile* PalaceTile::clone(){
	return new PalaceTile(getActionCount());
}


TileFactory::TileFactory(int _nTiles) : nTiles(_nTiles), max(_nTiles-1), tiles(_nTiles) {

	int numberForEach = (nTiles / 14);

	int desetTilesToInsert = nTiles - numberForEach*14;

	for (int i = 0; i < numberForEach; i++){
		tiles.push_back(Tile());
		tiles.push_back(RestaurantTile());
		tiles.push_back(SpiceMerchantTile());
		tiles.push_back(FabricManufacturesTile());
		tiles.push_back(JewelerTile());
		tiles.push_back(CartManufacturerTile());
		tiles.push_back(SmallMarketTile());
		tiles.push_back(SpiceMarketTile());
		tiles.push_back(JelewryMarketTile());
		tiles.push_back(FabricMarketTile());
		tiles.push_back(BlackMarketTile());
		tiles.push_back(CasinoTile());
		tiles.push_back(GemMerchantTile());
		tiles.push_back(PalaceTile());
	}

	for (int i = 0; i < desetTilesToInsert; i++){
		tiles.push_back(Tile());
	}

}

TileFactory* TileFactory::get(int _nTiles){
	if (!instance){
		instance = new TileFactory(_nTiles);
	}
	return instance;
}

Tile* TileFactory::next(){
	if (instance && max >= 0){

		// Get a random int within size of remaining tiles
		int i = rand() % (max + 1);

		// Get references to the tiles to switch
		Tile& chosenTile = tiles[i];
		Tile& maxTile = tiles[max];

		// Swithc tiles
		tiles[i] = maxTile;
		tiles[max] = chosenTile;

		// Decrement the size of remaining tiles
		max--;

		return &chosenTile;
	}
	return nullptr;
}