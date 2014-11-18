class Player {
	int gold;
	int ruby;
	int spice;
	int fabric;
	int jewel;
	int cart;
	int food;
public:
	/*
	* Returns true if the player has food to act with. False if there is
	* no food
	*/
	bool canAct() const;

	/*
	* Transfers one gold from this player to the one passed as a parameter.
	* Returns true if the transaction was successful and false if the current
	* player does not have any gold.
	*/
	bool pay(Player& player);

	/*
	* Decrements the player's food supply by one down to a minimum of 0.
	*/
	void eat();

	/*
	* Returns the total amount of goods in the player's posession
	*/
	int totalGoods();

	// Accessor methods for goods, gold, cart room and food
	int getGold(){ return gold; }
	void setGold(int num){ gold = num; }

	int getRuby(){ return ruby; }
	void setRuby(int num){ ruby = num; }

	int getSpice(){ return spice; }
	void setSpice(int num){ spice = num; }

	int getFabric(){ return fabric; }
	void setFabric(int num){ fabric = num; }

	int getJewel(){ return jewel; }
	void setJewel(int num){ jewel = num; }

	int getCart(){ return cart; }
	void setCart(int num){ cart = num; }

	int getFood(){ return food; }
	void setFood(int num){ food = num; }
};
