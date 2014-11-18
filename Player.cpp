#include "player.h"

/*
* Returns true if the player has food to act with. False if there is
* no food
*/
bool Player::canAct() const{
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
int Player::totalGoods(){
	int num = 0;
	num += getFabric();
	num += getSpice();
	num += getJewel();
	num += getRuby();
	return num;
}