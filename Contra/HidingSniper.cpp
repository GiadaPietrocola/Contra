#include "HidingSniper.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "Block.h"
#include "Bill.h"
#include "Bullet.h"
#include "Sounds.h"

using namespace Contra;

HidingSniper::HidingSniper(QPointF pos)
	: Enemy(pos, TILE, 2 * TILE)
{
	_sprite = Sprites::instance()->getSprite("Enemies");
	_fire = false;
	_hiding = true;
	_rising = false;
	_out = false;
	_dying = false;
	_viewDir = Direction::LEFT;


	_boundingRect.adjust(-3, 0, 3, 0);
	_collider.adjust(8, 20, -8, 0);

	Sprites::instance()->getAnimation("Hiding_Sniper_Hiding", &_animHiding);
	Sprites::instance()->getAnimation("Hiding_Sniper_Fire_Horizontal", &_animFireHorizontal);
	Sprites::instance()->getAnimation("Sniper_Dying", &_animDying[0]);


}

void HidingSniper::advance()
{

	Bill* player = Game::instance()->player();

	if (_hiding && !_rising) {
		_rising = true;
		schedule("rising", 100, [this]()
			{
				_hiding = false;
				_out = true;
				_rising = false;
			});

	}


	if ((player->x() - x() > -124 && player->x() - x() < 135) && !player->isDying())
	{
		if (_out && !_rising)
		{
			if ((player->x() - x()) > 0)
			{
				fire(1.0 / 3, 0, TILE, TILE - 4);
				_viewDir = Direction::RIGHT;
			}
			if ((player->x() - x()) < 0)
			{
				fire(-1.0 / 3, 0, 0, TILE - 4);
				_viewDir = Direction::LEFT;
			}
			_rising = true;
			schedule("hiding", 100, [this]()
				{
					_hiding = true;
					_out = false;
					_rising = false;

				});

		}
	}

	DynamicObject::advance();
}

void HidingSniper::animate()
{
	if (_dying)
		_animRect = &_animDying[_animCounter / 12];
	else if (_hiding)
		_animRect = &_animHiding;
	else
		_animRect = &_animFireHorizontal;

	_animCounter++;
}



void HidingSniper::paint(QPainter* painter)
{

	if (_viewDir == Direction::LEFT || _viewDir == Direction::UP_LEFT || _viewDir == Direction::DOWN_LEFT)
	{
		painter->translate(_boundingRect.width(), 0);
		painter->scale(-1, 1);


	}

	Object::paint(painter);
}

void HidingSniper::fire(double x_vel, double y_vel, double x_pos, double y_pos)
{
	if (_fire)
		return;

	_fire = true;

	new Bullet(QPoint(pos().x() + x_pos, pos().y() + y_pos), x_vel, y_vel, 1);

	schedule("fire_disable", 50, [this]()
		{
			_fire = false;

		});
}

bool HidingSniper::hit(Object* what, Direction fromDir)
{
	if (what->to<Bullet*>() && what->to<Bullet*>()->getOwner() == 0 && !_hiding)
	{

		Sounds::instance()->playSound("EnemyHit");

		if (fromDir == Direction::RIGHT)
			Die(-1);
		else
			Die(1);
	}
	return true;
}

void HidingSniper::Die(int Direction)
{
	if (!_dying)
	{

		_dying = true;
		velAdd(Vec2Df(Direction * 0.5, -3));
		_collider.adjust(_collider.width(), _collider.height(), 0, 0);
		_boundingRect.adjust(+2, 0, -2, 0);
		_animCounter = 0;

		schedule("Sniper_Die_1", 12, [this]()
			{
				_y_gravity = 0;
				velClipX(0);
				velClipY(0);
			});

		schedule("Sniper_Die_2", 48, [this]()
			{
				setVisible(false);
				_dead = true;
			});
	}
}