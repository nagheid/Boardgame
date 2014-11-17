#include "tile.h"
#include <iostream>
#include <cstdlib>

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

Tile* CartManufacturerTile::clone(){
	return &CartManufacturerTile();
}


// ----------------------------------------------------------------------------
// Small Market
// ----------------------------------------------------------------------------

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

	int numOfItems = rand() % 6;
	int space = player.getCart() - player.totalItems();

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
	return &BlackMarketTile();
}


// ----------------------------------------------------------------------------
// Casino
// ----------------------------------------------------------------------------

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
	return &PalaceTile();
}
