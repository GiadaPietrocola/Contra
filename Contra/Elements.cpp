#include "Elements.h"
#include "Game.h"
#include "GameConfig.h"
#include "Sprites.h"
#include "Bill.h"

using namespace Contra;

FlashingElements::FlashingElements() : Object(QPointF(0, 0), 3456, 229){
	
	_collider.adjust(0, 0, -3456, 0);
	_sprite = Sprites::instance()->getSprite("FlashingElements");

	Sprites::instance()->getAnimation("Flashing_elements", &_animFlashing[0]);
}

void FlashingElements::animate()
{
	_animRect = &_animFlashing[(FRAME_COUNT / 10) % 2];
}

Medals::Medals() : Object(QPointF(0, 0), TILE, TILE) {

	_sprite = Sprites::instance()->getSprite("Medals");

	_compenetrable = true;
	Sprites::instance()->getAnimation("Medals", &_animMedals[0]);

}

void Medals::animate()
{
	Bill* player = Game::instance()->player();

	_animRect = &_animMedals[player->lifes()];

	if (player->lifes() == 0)
		if(_boundingRect.width()==TILE)
			_boundingRect.adjust(0, 0, 51, 5);
			
}
void Medals:: advance()
{
	setX(Game::instance()->wiewRect().x());
}

Text::Text(std::string text) : Object(QPoint(50, 45), TILE * 8, TILE)
{
	_pixText = Sprites::instance()->getText(text, 0, QColor(255, 255, 255));
	_sprite = &_pixText;
	_animText = QRect(0, 0, TILE * 8, TILE);
	_animRect = &_animText;

	setZValue(1);
}

Title::Title() : Object(QPoint(0, 0), 10 * TILE, 9.2 * TILE)
{
	_sprite = Sprites::instance()->getSprite("title");
	_animTitle = QRect(0, 0, 10 * TILE, 9.2 * TILE);
	_animRect = &_animTitle;

	setX(TILE * 10);
	_moving = true;

	schedule("stop",TILE * 10, [this]()
		{
			_moving = false;
		});

	setZValue(1);
}

void Title::advance()
{
	if (_moving)
		setX(x() - 1);
}