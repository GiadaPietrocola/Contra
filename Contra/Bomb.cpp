#include "Bomb.h"
#include "GameConfig.h"
#include "Game.h"
#include "Sprites.h"
#include <QPainter>
#include "Bill.h"
#include "Sounds.h"
#include "Block.h"
#include "Explosion.h"

using namespace Contra;


Bomb::Bomb(QPointF pos) : DynamicObject(pos, 12, 12)
{

	_compenetrable = true;
	_collider.adjust(2, 2, -2, -2);
	defaultPhysics();

	_sprite = Sprites::instance()->getSprite("Bullet");

	Sprites::instance()->getAnimation("Bomb", &_animFire);

	_animRect = &_animFire;

	_y_gravity = 0.05;

	srand(time(0) + _id);
	_x_vel_max = ((rand() % 100) / (float)40 + 0.5);


}


void Bomb::advance()
{

	velAdd(Vec2Df(-0.2, 0));
	DynamicObject::advance();

}


bool Bomb::hit(Object* what, Direction fromDir)
{
	if (y() > 7 * TILE && what->to<Block*>()) {
		new Explosion(2, QPointF(x() - 12, y() - 12));
		setVisible(false);
		_dead = true;
		Sounds::instance()->playSound("BombExplosion");
	}
	if (what->to<Bill*>()) {
		setVisible(false);
		_dead = true;
	}
	return true;
}