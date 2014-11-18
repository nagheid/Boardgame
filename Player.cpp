#include "player.h"

bool Player::canAct() const{
	return (food > 0);
}

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

void Player::eat(){
	if (food > 0){
		food--;
	}
}

int Player::totalItems(){
	int num = 0;
	num += getFabric();
	num += getSpice();
	num += getJewel();
	num += getRuby();
	return num;
}