#include "TurretPowerUp.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "Explosion.h"
#include "Bill.h"
#include "Bullet.h"
#include "Block.h"

using namespace Contra;

TurretPowerUp::TurretPowerUp(QPointF pos, char type) : DynamicObject(pos, TILE + 7.5, TILE + 7.5)
{
	_sprite = Sprites::instance()->getSprite("PowerUps");
	_closed = true;
	_opening = false;
	_out = false;
	_open = false;
	_type = type;

	_y_gravity = 0;

	Sprites::instance()->getAnimation("Turret_power_up_closed", &_animClosed);
	Sprites::instance()->getAnimation("Turret_power_up", &_animOpen[0]);
	Sprites::instance()->getAnimation("Power_up", &_animOut[0]);

}

void TurretPowerUp::advance()
{
	Bill* player = Game::instance()->player();

	if (_life == 0 && !_out)
	{
		_collider.adjust(8, 19, -15, 2);
		_boundingRect.adjust(0, 17, -7, 0);
		_y_gravity = 0.1;
		_y_vel_max = 4;
		velAdd(Vec2Df(0.4, -4));
		_out = true;

		new Explosion(2, QPointF(x(), y()));
	}
	if (_out)
	{
		_closed = false;
		_open = false;
	}

	if ((player->x() - x() > -124 && player->x() - x() < 135) && !_out)
	{

		if (_closed && !_opening)
		{
			_opening = true;
			schedule("opening", 100, [this]()
				{
					_closed = false;
					_open = true;
					_opening = false;
				});
		}

		if (_open && !_opening)
		{
			_opening = true;
			schedule("closing", 100, [this]()
				{
					_closed = true;
					_open = false;
					_opening = false;

				});
		}
	}

	DynamicObject::advance();
}

bool TurretPowerUp::hit(Object* what, Direction fromDir)
{
	Bill* player = Game::instance()->player();

	if (what->to<Bullet*>() && what->to<Bullet*>()->getOwner() == 0 && !_closed)
	{
		if (player->PowerUp() == 'M')
			_life = _life - 2;
		else _life--;

	}
	if (what->to<Bill*>() && _out)
	{
		setVisible(false);
		_dead = true;
	}
	if (what->to<Block*>() && fromDir == Direction::DOWN && _out)
		velClipX(0);
	return true;
}


void TurretPowerUp::animate()
{

	if (_closed)
		_animRect = &_animClosed;
	else if (_out)
	{
		if (_type == 'R') {
			_animRect = &_animOut[0];
		}
		else if (_type == 'M') {
			_animRect = &_animOut[1];
		}
		else if (_type == 'B') {
			_animRect = &_animOut[2];
		}
	}
	else
		_animRect = &_animOpen[(FRAME_COUNT / 8) % 3];

}