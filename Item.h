#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Utilities.h"
#include "Player.h"
#include <map>

class Item {
	string itemName;
	Sprite* itemSprite;
protected:
	int value;
	Entity* model;
	Vector2f position;
	Vector2f destination;
public:
	Item(const string& itemName, const Vector2f& position);
	Item(const Item&);
	~Item();

	Texture* getTexture() const;
	Sprite*& getItemSprite();
	Vector2f getPosition() const;
	string getItemName() const;
	int getValue() const;

	void setSprite(Sprite*);
	void setName(const string&);
	void setValue(const int&);
	void setModel(Entity*);
	void setPosition(const Vector2f&);
	Vector2f getDestination() const;

	void removeItem(Frame& mainFrame);
	void animateItem();
	bool checkCollision(Player* _p);
};

class Slime : public Item {
public:
	Slime(const string& itemName, const Vector2f& position);
	~Slime();
};

class Coin : public Item {
public:
	Coin(const string& itemName, const Vector2f& position);
	~Coin();
};