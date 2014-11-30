#ifndef PLAYER_H
#define PLAYER_H

#include <istream>
#include <iostream>
#include <string>
#include <sstream>

using std::string;
using std::istream;
using std::ostream;

class Player;
istream& operator>>(istream&, Player&);
ostream& operator<<(ostream&, const Player&);

class Player {
	string name;
	int gold;
	int ruby;
	int spice;
	int fabric;
	int jewel;
	int cart;
	int food;

public:
	Player(string _name) :	name(_name), gold(5), 
							ruby(0), spice(1), 
							fabric(1), jewel(1),
							cart(9), food(10) {};

	/*
	 * Overloading operator== as Player is they key in the BoardGame hash map
	 */
	bool operator==(const Player& p) const;

	/*
	* Overloading >> and << operators
	*/
	friend ostream& operator<<(ostream& os, const Player& tile);
	friend istream& operator>>(istream& is, Player& tile);

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
	int totalGoods() const;

	// Accessor methods for name
	string getName() const { return name; }
	void setName(string _name) { name = _name; }

	// Accessor methods for goods, gold, cart room and food
	int getGold() const { return gold; }
	void setGold(int num){ gold = num; }

	int getRuby() const { return ruby; }
	void setRuby(int num){ ruby = num; }

	int getSpice() const { return spice; }
	void setSpice(int num){ spice = num; }

	int getFabric() const { return fabric; }
	void setFabric(int num){ fabric = num; }

	int getJewel() const { return jewel; }
	void setJewel(int num){ jewel = num; }

	int getCart() const { return cart; }
	void setCart(int num){ cart = num; }

	int getFood() const { return food; }
	void setFood(int num){ food = num; }
};

#endif