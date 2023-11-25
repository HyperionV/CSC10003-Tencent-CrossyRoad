#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Utilities.h"
#include "Player.h"


class Item {
	Frame mainFrame;
	Sprite* _item;
	Entity model;
	int value;
	Vector2f position;
public:
	Item(Frame& mainFrame, const Entity& model, const int& value, const Vector2f& position);

	void animateItem();
	void useItem(Player* _player);
};
