class Player {
	int gold;
	int ruby;
	int spice;
	int fabric;
	int jewel;
	int cart;
	int food;
public:
	bool canAct() const;
	bool pay(Player& player);
	void eat();
    int totalItems();

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
