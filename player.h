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
};
