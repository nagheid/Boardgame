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
    player.setFood(10);
    return true;
}

Tile* RestaurantTile::clone(){
	return &RestaurantTile();
}


// ----------------------------------------------------------------------------
// Spice Merchant
// ----------------------------------------------------------------------------

bool SpiceMerchantTile::action(Player& player){
    int space = player.getCart() - player.totalItems();
    if(player.getGold() >= 2 && space > 0){
        player.setGold(player.getGold() - 2);
        if(space < 3){
            player.setSpice(cart);
        }
        else{
            player.setSpice(player.getSpice() + 3);
        }
        return true;
    }
    return false;
}

Tile* SpiceMerchantTile::clone(){
	return &SpiceMerchantTile();
}


// ----------------------------------------------------------------------------
// Fabric Manufactures
// ----------------------------------------------------------------------------

bool FabricManufacturesTile::action(Player& player){
    int space = player.getCart() - player.totalItems();
    if(player.getGold() >= 2 && space > 0){
        player.setGold(player.getGold() - 2);
        if(space < 3){
            player.setFabric(cart);
        }
        else{
            player.setFabric(player.getFabric() + 3);
        }
        return true;
    }
    return false;
}

Tile* FabricManufacturesTile::clone(){
	return &FabricManufacturesTile();
}


// ----------------------------------------------------------------------------
// Jeweler
// ----------------------------------------------------------------------------

bool JewelerTile::action(Player& player){
    int space = player.getCart() - player.totalItems();
    if(player.getGold() >= 2 && space > 0){
        player.setGold(player.getGold() - 2);
        if(space < 3){
            player.setJewel(cart);
        }
        else{
            player.setJewel(player.getJewel() + 3);
        }
        return true;
    }
    return false;
}

Tile* JewelerTile::clone(){
	return &JewelerTile();
}


// ----------------------------------------------------------------------------
// Cart Manufacturer
// ----------------------------------------------------------------------------

bool CartManufacturerTile::action(Player& player){
    if(player.getGold() >= 7){
        player.setGold(player.getGold() - 7);
        player.setCart(player.getCart() + 3);
        return true;
    }
    return false;
}

Tile* CarManufacturerTile::clone(){
	return &CarManufacturerTile();
}


// ----------------------------------------------------------------------------
// Small Market
// ----------------------------------------------------------------------------

bool SmallMarketTile::action(Player& player){
    if(player.getFabric() > 0 && player.getJewel() > 0 && player.getFabric() > 0){
        player.setFabric(player.getFabric() - 1);
        player.setJewel(player.getJewel() - 1);
        player.setFabric(player.getFabric() -1);
        player.setGold(player.getGold() + 8;
        return true;
    }
    return false;
}

Tile* SmallMarketTile::clone(){
	return &SmallMarketTile();
}

// ----------------------------------------------------------------------------
// Spice Market
// ----------------------------------------------------------------------------

bool SpiceMarketTile::action(Player& player){
    if(player.getSpice() >= 3){
        player.setSpice(player.getSpice() - 3);
        player.setGold(player.getGold() + 6);
    }
}

Tile* SpiceMarketTile::clone(){
	return &SpiceMarketTile();
}


// ----------------------------------------------------------------------------
// Jelewry Market
// ----------------------------------------------------------------------------

bool JelewryMarketTile::action(Player& player){
    if(player.getJewel() >= 3){
        player.setJewel(player.getJewel() - 3);
        player.setGold(player.getGold() + 6);
    }
}

Tile* JelewryMarketTile::clone(){
	return &JelewryMarketTile();
}


// ----------------------------------------------------------------------------
// Fabric Market
// ----------------------------------------------------------------------------

bool FabricMarketTile::action(Player& player){
    if(player.getFabric() >= 3){
        player.setFabric(player.getFabric() - 3);
        player.setGold(player.getGold() + 6);
    }
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
