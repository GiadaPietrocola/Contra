#include "FlyingPowerUp.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Bill.h"

using namespace Contra;

FlyingPowerUp::FlyingPowerUp(QPointF pos, char type) : DynamicObject(pos, TILE, 15)
{
	_sprite = Sprites::instance()->getSprite("PowerUps");

	Sprites::instance()->getAnimation("Flying_PowerUp", &_animFlying);
	Sprites::instance()->getAnimation("Power_up", &_animPowerUp[0]);

	_collider.adjust(8, 2, -8, -2);

	_x_dir = Direction::LEFT;
	_y_gravity = 0;
	_y_acc_jmp = 2;
	_x_vel_max = 1.2;

	setVisible(false);

	_flying = true;



	_type = type;

}

void FlyingPowerUp::advance()
{

	Bill* player = Game::instance()->player();

	if (isVisible() && _flying)
	{
		if (y() < 10)
		{
			velAdd(Vec2Df(_x_acc, 0));
			velAdd(Vec2Df(0, _y_acc_jmp));
		}
		else if (y() > 60)
		{
			velAdd(Vec2Df(_x_acc, 0));
			velAdd(Vec2Df(0, -_y_acc_jmp));
		}
	}

	DynamicObject::advance();

	if (x() < (Game::instance()->wiewRect().x()) && x() < player->x() && _flying)
		setVisible(true);


}

bool FlyingPowerUp::hit(Object* what, Direction fromDir)
{
	if (what->to<Bullet*>() && what->to<Bullet*>()->getOwner() == 0 && _flying)
	{
		new Explosion(2, pos());
		_collider.adjust(0, 0, 0, 4);
		_y_gravity = 0.1;
		_flying = false;
		velClipX(0);
		velClipY(0);

		if (_type == 'R')
		{
			_animRect = &_animPowerUp[0];
		}
		else if (_type == 'M')
		{
			_animRect = &_animPowerUp[1];
		}
		else if (_type == 'B')
		{
			_animRect = &_animPowerUp[2];
		}
	}
	if (what->to<Bill*>() && !_flying)
	{
		setVisible(false);
		_dead = true;
	}

	return true;
}


void FlyingPowerUp::animate()
{
	if (_flying)
		_animRect = &_animFlying;

}