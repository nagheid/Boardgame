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
    inline int getGold(){return gold;}
    inline void setGold(int num){gold = num;}
    inline int getRuby(){return ruby;}
    inline void setRuby(int num){ruby = num;}
    inline int getSpice(){return spice;}
    inline void setSpice(int num){spice = num;}
    inline int getFabric(){return fabric;}
    inline void setFabric(int num){fabric = num;}
    inline int getJewel(){return jewel;}
    inline void setJewel(int num){jewel = num;}
    inline int getCart(){return cart;}
    inline void setCart(int num){cart = num;}
    inline int getFood(){return food};
    inline void setFood(int num){food = num};
};
