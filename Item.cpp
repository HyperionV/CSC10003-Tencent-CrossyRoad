#pragma warning(disable:4244)
#include "Item.h"

Item::Item(const string& _itemName, const Vector2f& position)
	:itemName{_itemName}, position{ position }
{
	itemSprite = nullptr;
}

Item::Item(const Item& item)
	:Item(item.itemName, item.position)
{}

Item::~Item() {
	delete model;
}

void Item::setSprite(Sprite* _sprite) {
	itemSprite = _sprite;
}

void Item::setName(const string& _name) {
	itemName = _name;
}

void Item::setValue(const int& val) {
	value = val;
}

void Item::setModel(Entity* _model) {
	model = _model;
}

void Item::setPosition(const Vector2f& _pos) {
	position = _pos;
}

Texture* Item::getTexture() const {
	return model->getCurrentTexture();
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

void Item::removeItem(Frame& mainFrame) {
	mainFrame.removeSprite(itemSprite);
}

void Item::animateItem() {
	model->shiftResource();
	itemSprite->setTexture(model->getCurrentTexture());
}

bool Item::checkCollision(Player* _p) {
	Vector2f hitbox(30, 30);
	Vector2f topLeft = _p->getCurrentPos();
	Vector2f bottomRight = topLeft + _p->getHitbox();
	if (topLeft.x > bottomRight.x) {
		swap(topLeft.x, bottomRight.x);
	}
	if (topLeft.y < bottomRight.y) {
		swap(topLeft.y, bottomRight.y);
	}
	
	Vector2f vTopLeft = itemSprite->getPosition();
	Vector2f vBottomRight = vTopLeft + hitbox;
	if (vTopLeft.x > vBottomRight.x) {
		swap(vTopLeft.x, vBottomRight.x);
	}
	if (vTopLeft.y < vBottomRight.y) {
		swap(vTopLeft.y, vBottomRight.y);
	}
	if (bottomRight.x < vTopLeft.x || vBottomRight.x < topLeft.x) return true;
	if (topLeft.y < vBottomRight.y || vTopLeft.y < bottomRight.y) return true;
	return false;

}

Slime::Slime(const string& _itemName, const Vector2f& _position)
	:Item(_itemName, _position)
{
	value = -2;
	model = new Entity("blueSlime_jumpattack");
	this->position.y -= 15;
	this->destination = Vector2f((this->position.x == -132) ? 1280 : -132, this->position.y);
}

Vector2f Item::getDestination() const {
	return destination;
}

Coin::Coin(const string& _itemName, const Vector2f& _position)
	:Item(_itemName, _position)
{
	model = new Entity("yc");
	value = 5;
	destination = position;
}
