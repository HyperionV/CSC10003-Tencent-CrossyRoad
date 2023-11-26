#include "Item.h"

Item::Item(const string& itemName, const Entity& model, const int& value, const Vector2f& position)
	:model{model}, value{value}, position{position}
{
	cout << "Getting called bruh" << endl;
	itemSprite = nullptr;
}

//Item::Item(const Entity& model, const int& value, const Vector2f& position)
//	:model{ model }, value{ value }, position{ position }
//{
//	itemSprite = nullptr;
//}

Item::Item(const Item& item)
	:Item(item.itemName, item.model, item.value, item.position)
{}

Item::~Item() {
	cout << "Destroying item" << endl;
}

void Item::setSprite(Sprite* _sprite) {
	itemSprite = _sprite;
}

void Item::setName(const string& _name) {
	itemName = _name;
}

void Item::setModel(const Entity& _e) {
	model = _e;
}

void Item::setValue(const int& val) {
	value = val;
}

void Item::setPosition(const Vector2f& _pos) {
	position = _pos;
}

Texture* Item::getTexture() const {
	return model.getCurrentTexture();
}

Sprite*& Item::getItemSprite() {
	return itemSprite;
}

Vector2f Item::getPosition() const {
	return position;
}

string Item::getItemName() const {
	return itemName;
}

int Item::getValue() const {
	return value;
}

void Item::animateItem() {
	model.shiftResource();
}

bool Item::useItem(Player* _player) {
	if (_player->getCurrentPos() == position) {
		_player->addPoint(value);
		return true;
	}
	return false;
}

//Slime::Slime(const string& _itemName, const Entity& _model, const int& _value, const Vector2f& _position, const Vector2f& _destination, const float& _speed)
//	:Item(_itemName, _model, _value, _position), destination{ _destination }, speed{ _speed }
//{}

//Slime::Slime(const Entity& _model, const int& _value, const Vector2f& _position, const Vector2f& _destination, const float& _speed)
//	:Item(_model, _value, _position), destination{ _destination }, speed{ _speed }
//{}

//Coin::Coin(const string& _itemName, const Entity& _model, const int& _value, const Vector2f& _position)
//	:Item(_itemName, _model, _value, _position)
//{}

//Coin::Coin(const Entity& _model, const int& _value, const Vector2f& _position)
//	:Item(_model, _value, _position)
//{}
