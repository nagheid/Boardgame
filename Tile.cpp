#include "tile.h"
#include <iostream>

using namespace std;


// ----------------------------------------------------------------------------
// Desert (Default Tile)
// ----------------------------------------------------------------------------

bool Tile::operator==(const Tile &t){

}

bool Tile::action(Player& player){
	return false;
}

Tile* Tile::clone(){
	return &Tile();
}

ostream& Tile::operator<<(ostream& os){

}


// ----------------------------------------------------------------------------
// Restaurant
// ----------------------------------------------------------------------------

bool RestaurantTile::action(Player& player){

}

Tile* RestaurantTile::clone(){
	return &RestaurantTile();
}


// ----------------------------------------------------------------------------
// Spice Merchant
// ----------------------------------------------------------------------------

bool SpiceMerchantTile::action(Player& player){

}

Tile* SpiceMerchantTile::clone(){
	return &SpiceMerchantTile();
}


// ----------------------------------------------------------------------------
// Fabric Manufactures
// ----------------------------------------------------------------------------

bool FabricManufacturesTile::action(Player& player){

}

Tile* FabricManufacturesTile::clone(){
	return &FabricManufacturesTile();
}


// ----------------------------------------------------------------------------
// Jeweler
// ----------------------------------------------------------------------------

bool JewelerTile::action(Player& player){

}

Tile* JewelerTile::clone(){
	return &JewelerTile();
}


// ----------------------------------------------------------------------------
// Car Manufacturer
// ----------------------------------------------------------------------------

bool CarManufacturerTile::action(Player& player){

}

Tile* CarManufacturerTile::clone(){
	return &CarManufacturerTile();
}


// ----------------------------------------------------------------------------
// Small Market
// ----------------------------------------------------------------------------

bool SmallMarketTile::action(Player& player){

}

Tile* SmallMarketTile::clone(){
	return &SmallMarketTile();
}

// ----------------------------------------------------------------------------
// Spice Market
// ----------------------------------------------------------------------------

bool SpiceMarketTile::action(Player& player){

}

Tile* SpiceMarketTile::clone(){
	return &SpiceMarketTile();
}


// ----------------------------------------------------------------------------
// Jelewry Market
// ----------------------------------------------------------------------------

bool JelewryMarketTile::action(Player& player){

}

Tile* JelewryMarketTile::clone(){
	return &JelewryMarketTile();
}


// ----------------------------------------------------------------------------
// Fabric Market
// ----------------------------------------------------------------------------

bool FabricMarketTile::action(Player& player){

}

Tile* FabricMarketTile::clone(){
	return &FabricMarketTile();
}

// ----------------------------------------------------------------------------
// Black Market
// ----------------------------------------------------------------------------

bool BlackMarketTile::action(Player& player){

}

Tile* BlackMarketTile::clone(){
	return &BlackMarketTile();
}


// ----------------------------------------------------------------------------
// Casino
// ----------------------------------------------------------------------------

bool CasinoTile::action(Player& player){

}

Tile* CasinoTile::clone(){
	return &CasinoTile();
}

// ----------------------------------------------------------------------------
// Gem Merchant
// ----------------------------------------------------------------------------

bool GemMerchantTile::action(Player& player){

}

Tile* GemMerchantTile::clone(){
	return &GemMerchantTile();
}

// ----------------------------------------------------------------------------
// Palace
// ----------------------------------------------------------------------------

bool PalaceTile::action(Player& player){

}

Tile* PalaceTile::clone(){
	return &PalaceTile();
}