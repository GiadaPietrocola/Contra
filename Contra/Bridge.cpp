#include "Bridge.h"
#include "Bill.h"
#include "Game.h"
#include "GameConfig.h"
#include "Sprites.h"
#include "Explosion.h"

using namespace Contra;

Bridge::Bridge(QPointF pos, double width, double height) :	StaticObject(pos, width, height) {
	_exploding = false;

	_boundingRect = QRectF(0, 0, width, TILE);
	_boundingRect.adjust(0,-7,0,0);

	Sprites::instance()->getAnimation("Bridge", &_animBridge[0]);
	Sprites::instance()->getAnimation("Bridge_exploding_1", &_animExplosion[0][0]);
	Sprites::instance()->getAnimation("Bridge_exploding_2", &_animExplosion[1][0]);
	Sprites::instance()->getAnimation("Bridge_exploding_3", &_animExplosion[2][0]);
	_sprite = Sprites::instance()->getSprite("Bridge");

	_explodingTime = 0;

}

void Bridge::advance() {

	Bill* player = Game::instance()->player();

	if (player->x() > x())
		explode();

	if (_exploding){
		if(_explodingTime == 1 && _collider.width() == 4.08 * TILE) {

			_collider.adjust(1.28 * TILE, 0, 0, 0);
			_boundingRect.adjust(1.28 * TILE, 0, 0, 0);
		}
		if (_explodingTime == 2 && _collider.width() == 2.8 * TILE) {
			
			_collider.adjust(1.28 * TILE, 0, 0, 0);
			_boundingRect.adjust(1.28 * TILE, 0, 0, 0);
		}
		if (_explodingTime == 3 && _collider.width() == 1.52 * TILE) {

			_collider.adjust(1.56 * TILE, 0, 0, 0);
			_boundingRect.adjust(1.56 * TILE, 0, 0, 0);
		}
	}
}

void Bridge::animate() {

	if(!_exploding)
		_animRect = &_animBridge[(FRAME_COUNT / 8) % 3];
	else 
		_animRect = &_animExplosion[_explodingTime][(FRAME_COUNT / 8) % 3];
}

void Bridge::explode() {

	if (_exploding)
		return;

	_exploding = true;

	_collider.adjust(1.04 * TILE, 0, 0, 0);
	_boundingRect.adjust(1.04 * TILE, 0, 0, 0);

	new Explosion(1,QPointF(x(), y() - TILE));

	schedule("explode1", 52, [this]()
		{
			_explodingTime++;
			new Explosion(1, QPointF(x()+1.28 * TILE, y() - TILE));

			schedule("explode2", 52, [this]()
				{
					_explodingTime++;
					new Explosion(1, QPointF(x() + 2.56 * TILE, y()-TILE));

					schedule("explode3", 52, [this]()
						{
							_explodingTime++;
							new Explosion(1, QPointF(x() + 4.12 * TILE, y() - TILE));

							setVisible(false);
						});
				});
		});
}