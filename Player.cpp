#include "player.h"

/*
 * Overloading operator== as Player is they key in the BoardGame hash map
 */
bool Player::operator==(const Player &p) const {
	return this->name == p.name;
}

/*
* Returns true if the player has food to act with. False if there is
* no food
*/
bool Player::canAct() const {
	return (food > 0);
}

/*
* Transfers one gold from this player to the one passed as a parameter.
* Returns true if the transaction was successful and false if the current
* player does not have any gold.
*/
bool Player::pay(Player& player){
	if (gold > 0){
		setGold(getGold() - 1);
		player.setGold(getGold() + 1);
		return true;
	}
	else{
		return false;
	}
}

/*
* Decrements the player's food supply by one down to a minimum of 0.
*/
void Player::eat(){
	if (food > 0){
		food--;
	}
}

/*
* Returns the total amount of goods in the player's posession
*/
int Player::totalGoods() const {
	int num = 0;
	num += getFabric();
	num += getSpice();
	num += getJewel();
	num += getRuby();
	return num;
}

/*
* Overloading >> and << operators
*/
ostream& operator<<(ostream& os, const Player& player) {
	os << "Player: " << player.getName() << "\t";
	os << "Food: " << player.getFood() << "; ";
	os << "Gold: " << player.getGold() << "; ";
	os << "Fabric: " << player.getFabric() << "; ";
	os << "Spices: " << player.getSpice() << "; ";
	os << "Jeweles: " << player.getJewel() << "; ";
	os << "Rubies: " << player.getRuby() << "; ";
	os << "Space in cart: " << player.getCart() - player.totalGoods();
	os << std::endl;
	return os;
}

istream& operator>>(istream& is, Player& player) {
	// TODO
	is >> player.name >> player.food;
	return is;
}