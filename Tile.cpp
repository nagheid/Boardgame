#include "tile.h"
#include <iostream>
#include <cstdlib>

using namespace std;

static int ID = 0;

// ----------------------------------------------------------------------------
// Desert (Default Tile)
// No action is possible on this tile. This is the base class behaviour
// ----------------------------------------------------------------------------

Tile::Tile(int _actionCount) : actionCount(_actionCount), id(++ID), name("Desert"),
								description("No action is possible on this tile.") {}

bool Tile::operator==(const Tile &t) const {
	return this->id == t.id;
}

bool Tile::action(Player& player){
	actionCount++;
	return false;
}

bool Tile::actionValid(Player& player, int numOfOtherPlayers){
	return false;
}

Tile* Tile::clone(){
	return new Tile(getActionCount());
}

ostream& operator<<(ostream& os, const Tile& tile){
	os << tile.id << "\t" << tile.name << "\t" << tile.actionCount << endl;
	return os;
}

istream& operator>>(istream& is, Tile& tile){
	// Store stream into tokens vector
	string line, token;	getline(is, line);
	std::istringstream streamLine(line);
	vector<string> tokens;
	copy(istream_iterator<string>(streamLine),
		istream_iterator<string>(),
		back_inserter(tokens));

	// Parse the tokens
	tile.id = std::stoi(tokens[0]);
	tile.actionCount = std::stoi(tokens[tokens.size() - 1]);
	string name;
	for (int i = 1; i < tokens.size() - 1; i++) {
		name += tokens[i];
	}
	tile.name = name;

	return is;
}


// ----------------------------------------------------------------------------
// Restaurant
// The number of food items of a player is replenished and will be set to 10.
// This is the initial position of all players.
// ----------------------------------------------------------------------------

RestaurantTile::RestaurantTile(int _actionCount) : Tile(_actionCount) {
	name = "Restaurant";
	description = "The number of food items of a player is replenished and will "
		"be set to 10.";
}

bool RestaurantTile::action(Player& player){
    player.setFood(10);
	cout << player.getName() << "'s food supply set to 10." << endl;
	Tile::action(player);
    return true;
}

bool RestaurantTile::actionValid(Player& player, int numOfOtherPlayers){
	if ((player.getGold() - numOfOtherPlayers) >= 2){
		return true;
	}
	return false;
}

Tile* RestaurantTile::clone(){
	return &RestaurantTile();
}

// ----------------------------------------------------------------------------
// Spice Merchant
// For 2 pieces of gold, a player can purchase 3 sacks of spices (less if the
// player does not have a capacity in his / her cart).
// ----------------------------------------------------------------------------

SpiceMerchantTile::SpiceMerchantTile(int _actionCount) : Tile(_actionCount) {
	name = "Spice Merchant";
	description = "For 2 pieces of gold, a player can purchase 3 sacks of spices "
		"(less if the player does not have a capacity in his / her cart).";
}

bool SpiceMerchantTile::action(Player& player){
	int space = player.getCart() - player.totalGoods();
    if(player.getGold() >= 2 && space > 0){
        player.setGold(player.getGold() - 2);
        if(space < 3){
			player.setSpice(player.getSpice() + space);
			cout << "Added " << space << " spices to " + player.getName() << endl;
        }
        else{
            player.setSpice(player.getSpice() + 3);
			cout << "Added 3 spices to " + player.getName() << endl;
        }
		Tile::action(player);
        return true;
    }
    return false;
}

bool SpiceMerchantTile::actionValid(Player& player, int numOfOtherPlayers){
	int space = player.getCart() - player.totalGoods();
	if ((player.getGold() - numOfOtherPlayers) >= 2 && space > 0){
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

FabricManufacturesTile::FabricManufacturesTile(int _actionCount) : Tile(_actionCount) {
	name = "Fabric Manufactures";
	description = "For 2 pieces of gold, the player gets three rolls of fabrics "
		"tissues (less if the player does not have a capacity in his / her cart).";
}

bool FabricManufacturesTile::action(Player& player){
	int space = player.getCart() - player.totalGoods();
    if(player.getGold() >= 2 && space > 0){
        player.setGold(player.getGold() - 2);
        if(space < 3){
			player.setFabric(player.getFabric() + space);
			cout << "Added " << space << " fabrics to " + player.getName() << endl;
        }
        else{
            player.setFabric(player.getFabric() + 3);
			cout << "Added 3 fabrics to " + player.getName() << endl;
        }
		Tile::action(player);
        return true;
    }
    return false;
}

bool FabricManufacturesTile::actionValid(Player& player, int numOfOtherPlayers){
	int space = player.getCart() - player.totalGoods();
	if ((player.getGold() - numOfOtherPlayers) >= 2 && space > 0){
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

JewelerTile::JewelerTile(int _actionCount) : Tile(_actionCount) {
	name = "Jeweler";
	description = "For 2 pieces of gold, the player gets 3 pieces of jewelry (less "
		"if the player does not have a capacity in his / her cart).";
}

bool JewelerTile::action(Player& player){
	int space = player.getCart() - player.totalGoods();
    if(player.getGold() >= 2 && space > 0){
        player.setGold(player.getGold() - 2);
        if(space < 3){
			player.setJewel(player.getJewel() + space);
			cout << "Added " << space << " jewels to " + player.getName() << endl;
        }
        else{
            player.setJewel(player.getJewel() + 3);
			cout << "Added 3 jewels to " + player.getName() << endl;
        }
		Tile::action(player);
        return true;
    }
    return false;
}

bool JewelerTile::actionValid(Player& player, int numOfOtherPlayers){
	int space = player.getCart() - player.totalGoods();
	if ((player.getGold() - numOfOtherPlayers) >= 2 && space > 0){
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

CartManufacturerTile::CartManufacturerTile(int _actionCount) : Tile(_actionCount) {
	name = "Cart Manufacturer";
	description = "For 7 pieces of gold, the capacity of the cart is increased by 3.";
}

bool CartManufacturerTile::action(Player& player){
    if(player.getGold() >= 7){
        player.setGold(player.getGold() - 7);
        player.setCart(player.getCart() + 3);
		cout << "Added 3 to cart space to " + player.getName() << endl;
		Tile::action(player);
        return true;
    }
    return false;
}

bool CartManufacturerTile::actionValid(Player& player, int numOfOtherPlayers){
	if (player.getGold() >= (7 + numOfOtherPlayers)){
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

SmallMarketTile::SmallMarketTile(int _actionCount) : Tile(_actionCount) {
	name = "Small Market";
	description = "A player can sell 1 roll of fabric, 1 jewel and 1 sack of "
		"spices for 8 pieces of gold.";
}

bool SmallMarketTile::action(Player& player){
    if(player.getFabric() > 0 && player.getJewel() > 0 && player.getFabric() > 0){
        player.setFabric(player.getFabric() - 1);
        player.setJewel(player.getJewel() - 1);
        player.setFabric(player.getFabric() -1);
        player.setGold(player.getGold() + 8);
		cout << "Added 8 gold to " + player.getName() << endl;
		Tile::action(player);
        return true;
    }
    return false;
}

bool SmallMarketTile::actionValid(Player& player, int numOfOtherPlayers){
	if (player.getFabric() > 0 && player.getJewel() > 0 && player.getFabric() > 0
			&& player.getGold() >= numOfOtherPlayers){
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

SpiceMarketTile::SpiceMarketTile(int _actionCount) : Tile(_actionCount)  {
	name = "Spice Market";
	description = "A player can sell 3 sacks of spices for 6 pieces of gold.";
}

bool SpiceMarketTile::action(Player& player){
    if(player.getSpice() >= 3){
        player.setSpice(player.getSpice() - 3);
        player.setGold(player.getGold() + 6);
		cout << "Added 6 gold to " + player.getName() << endl;
		Tile::action(player);
		return true;
    }
	return false;
}

bool SpiceMarketTile::actionValid(Player& player, int numOfOtherPlayers){
	if (player.getSpice() >= 3 && player.getGold() >= numOfOtherPlayers){
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

JelewryMarketTile::JelewryMarketTile(int _actionCount) : Tile(_actionCount)  {
	name = "Jewelry Market";
	description = "A player can sell 3 pieces of jewelry for 6 pieces of gold.";
}

bool JelewryMarketTile::action(Player& player){
    if(player.getJewel() >= 3){
        player.setJewel(player.getJewel() - 3);
        player.setGold(player.getGold() + 6);
		cout << "Added 6 gold to " + player.getName() << endl;
		Tile::action(player);
		return true;
    }
	return false;
}

bool JelewryMarketTile::actionValid(Player& player, int numOfOtherPlayers){
	if (player.getJewel() >= 3 && player.getGold() >= numOfOtherPlayers){
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

FabricMarketTile::FabricMarketTile(int _actionCount) : Tile(_actionCount)  {
	name = "Fabric Market";
	description = "A player can sell 3 rolls of fabrics for 6 pieces of gold.";
}

bool FabricMarketTile::action(Player& player){
    if(player.getFabric() >= 3){
        player.setFabric(player.getFabric() - 3);
        player.setGold(player.getGold() + 6);
		cout << "Added 6 gold to " + player.getName() << endl;
		Tile::action(player);
		return true;
    }
	return false;
}

bool FabricMarketTile::actionValid(Player& player, int numOfOtherPlayers){
	if (player.getFabric() >= 3 && player.getGold() >= numOfOtherPlayers){
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

BlackMarketTile::BlackMarketTile(int _actionCount) : Tile(_actionCount)  {
	name = "Black Market";
	description = "For 1 piece of gold, a player can get between 0 and 5 goods "
		"at random (less if the player does not have a capacity in his / her cart).";
}

bool BlackMarketTile::action(Player& player){

	if (player.getGold() < 1){
		return false;
	}

	int numOfItems = rand() % 6;
	int space = player.getCart() - player.totalGoods();

	if (space < numOfItems){
		numOfItems = space;
	}

	for (int i = 0; i < numOfItems; i++){
		int tileNum = rand() % 4 + 1;
		if (tileNum == 1){
			player.setSpice(player.getSpice() + 1);
			cout << "Added 1 spice to " + player.getName() << endl;
		}
		else if (tileNum == 2){
			player.setFabric(player.getFabric() + 1);
			cout << "Added 1 fabric to " + player.getName() << endl;
		}
		else if (tileNum == 3){
			player.setJewel(player.getJewel() + 1);
			cout << "Added 1 jewel to " + player.getName() << endl;
		}
		else if (tileNum == 4){
			player.setRuby(player.getRuby() + 1);
			cout << "Added 1 ruby to " + player.getName() << endl;
		}
	}
	Tile::action(player);
	return true;
}

bool BlackMarketTile::actionValid(Player& player, int numOfOtherPlayers){
	if (player.getGold() >= (1+numOfOtherPlayers)){
		Tile::action(player);
		return true;
	}
	return false;
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

CasinoTile::CasinoTile(int _actionCount) : Tile(_actionCount)  {
	name = "Casino";
	description = "For 1 piece of gold, the player has 2 in 5 chance to loose, "
				  "i.e., win 0 pieces of gold, a 3 out of 10 chance to get 2 "
				  "pieces of gold, a 2 out of 10 chance to get 3 pieces of gold "
				  "and a 1 in 10 chance to win 10 pieces of gold.";
}

bool CasinoTile::action(Player& player){
	if (player.getGold() < 1){
		return false;
	}

	int num = rand() % 10 + 1;

	if (num == 1){
		player.setGold(player.getGold() + 10);
		cout << player.getName() << " won 10 gold." << endl;
	}
	else if (num > 1 && num < 4){
		player.setGold(player.getGold() + 3);
		cout << player.getName() << " won 3 gold." << endl;
	}
	else if (num > 3 && num < 7){
		player.setGold(player.getGold() + 2);
		cout << player.getName() << " won 2 gold." << endl;
	}
	else{
		cout << "Sorry, no winnings." + player.getName() << endl;
	}
	Tile::action(player);
	return true;
}

bool CasinoTile::actionValid(Player& player, int numOfOtherPlayers){
	if (player.getGold() >= (1 + numOfOtherPlayers)){
		return true;
	}
	return false;
}

Tile* CasinoTile::clone(){
	return new CasinoTile(getActionCount());
}

// ----------------------------------------------------------------------------
// Gem Merchant
// A player can buy a ruby. The first ruby costs 12 gold coins, the second ruby
// to be purchased costs 13, the third 14, etc.
// ----------------------------------------------------------------------------

GemMerchantTile::GemMerchantTile(int _actionCount) : Tile(_actionCount)  {
	name = "Gem Merchant";
	description = "A player can buy a ruby. The first ruby costs 12 gold coins, "
		"the second ruby to be purchased costs 13, the third 14, etc.";
}

bool GemMerchantTile::action(Player& player) {
	int nextSellPrice = 12 + getActionCount();
	if (player.getGold() >= nextSellPrice){
		player.setGold(player.getGold() - nextSellPrice);
		player.setRuby(player.getRuby() + 1);
		Tile::action(player);
		cout << "Added 1 ruby to " << player.getName() << endl;
		return true;
	}
	return false;
}

bool GemMerchantTile::actionValid(Player& player, int numOfOtherPlayers){
	int nextSellPrice = 12 + getActionCount();
	if (player.getGold() >= (nextSellPrice + numOfOtherPlayers)){
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

PalaceTile::PalaceTile(int _actionCount) : Tile(_actionCount)  {
	name = "Palace";
	description = "A player can get a ruby in exchange for 5 rolls of fabrics, "
		"5 pieces of jewelry and 5 sacks of spices.";
}

bool PalaceTile::action(Player& player){
	if (player.getFabric() >= 5 && player.getJewel() >= 5 && player.getSpice() >= 5){
		player.setFabric(player.getFabric() - 5);
		player.setJewel(player.getJewel() - 5);
		player.setSpice(player.getSpice() - 5);
		player.setRuby(player.getRuby() + 1);
		cout << "Added 1 ruby to " << player.getName() << endl;
		Tile::action(player);
		return true;
	}
	return false;
}

bool PalaceTile::actionValid(Player& player, int numOfOtherPlayers){
	int nextSellPrice = 12 + getActionCount();
	if (player.getFabric() >= 5 && player.getJewel() >= 5 && player.getSpice() >= 5
		&& player.getGold() >= numOfOtherPlayers){
		return true;
	}
	return false;
}

Tile* PalaceTile::clone(){
	return new PalaceTile(getActionCount());
}


// ----------------------------------------------------------------------------
// Tile Factory
// ----------------------------------------------------------------------------

TileFactory* TileFactory::instance = 0;

TileFactory::TileFactory(int _nTiles) : nTiles(_nTiles), max(_nTiles-1), tiles() {

	int numberForEach = (nTiles / 14);

	int desetTilesToInsert = nTiles - numberForEach*14;

	for (int i = 0; i < numberForEach; i++){
		tiles.push_back(new Tile());
		tiles.push_back(new RestaurantTile());
		tiles.push_back(new SpiceMerchantTile());
		tiles.push_back(new FabricManufacturesTile());
		tiles.push_back(new JewelerTile());
		tiles.push_back(new CartManufacturerTile());
		tiles.push_back(new SmallMarketTile());
		tiles.push_back(new SpiceMarketTile());
		tiles.push_back(new JelewryMarketTile());
		tiles.push_back(new FabricMarketTile());
		tiles.push_back(new BlackMarketTile());
		tiles.push_back(new CasinoTile());
		tiles.push_back(new GemMerchantTile());
		tiles.push_back(new PalaceTile());
	}

	for (int i = 0; i < desetTilesToInsert; i++){
		tiles.push_back(new Tile());
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
		Tile* chosenTile = tiles[i];
		Tile* maxTile = tiles[max];

		// Switch tiles
		tiles[i] = maxTile;
		tiles[max] = chosenTile;

		// Decrement the size of remaining tiles
		max--;

		return chosenTile;
	}
	return nullptr;
}