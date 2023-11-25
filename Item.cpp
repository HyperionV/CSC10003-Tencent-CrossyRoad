#include "Item.h"

Item::Item(Frame& mainFrame, const Entity& model, const int& value, const Vector2f& position)
	:mainFrame{mainFrame}, model{model}, value{value}, position{position}
{
	_item = mainFrame.addSprite(this->model.getCurrentTexture(), this->position);
}

void Item::animateItem() {
	model.shiftResource();
	_item->setTexture(model.getCurrentTexture());
}

void Item::useItem(Player* _player) {
	if (_player->getCurrentPos() == position) {
		_player->addPoint(value);
		mainFrame.removeSprite(_item);
		_item = nullptr;
	}
}

