#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Utilities.h"
#include "Player.h"

class Item {
	string itemName;
	Entity model;
	int value;
	Vector2f position;
	Sprite* itemSprite;
public:
	Item(const string& itemName, const Entity& model, const int& value, const Vector2f& position);
	Item(const Item&);

	Texture* getTexture() const;
	Sprite*& getItemSprite();
	Vector2f getPosition() const;
	string getItemName() const;
	int getValue() const;

	void setSprite(Sprite*);
	void setName(const string&);
	void setModel(const Entity&);
	void setValue(const int&);
	void setPosition(const Vector2f&);

	void animateItem();
	bool useItem(Player* _player);
};

//class Slime : public Item {
//public:
//	Slime(const string& itemName, const Entity& model, const int& value, const Vector2f& position, const Vector2f& destination, const float& speed);;
//	//Slime(const Entity& model, const int& value, const Vector2f& position, const Vector2f& destination, const float& speed);
//};
//
//class Coin : public Item {
//public:
//	Coin(const string& itemName, const Entity& model, const int& value, const Vector2f& position);
//	//Coin(const Entity& model, const int& value, const Vector2f& position);
//};