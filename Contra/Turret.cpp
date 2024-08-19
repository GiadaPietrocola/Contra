#include "Turret.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "Block.h"
#include "Bill.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Sounds.h"

using namespace Contra;

Turret::Turret(QPointF pos) : Enemy(pos, TILE + 7.5, TILE + 7.5)
{
	_sprite = Sprites::instance()->getSprite("Towers");
	_fire = false;
	_firing = false;
	_closed = true;
	_opening = false;
	_viewDir = Direction::NONE;
	_prevViewDir = Direction::NONE;

	_y_gravity = 0;

	Sprites::instance()->getAnimation("Turret_Close", &_animClose[0]);
	Sprites::instance()->getAnimation("Turret_Fire_Right", &_animFireRight[0]);
	Sprites::instance()->getAnimation("Turret_Fire_Left", &_animFireLeft[0]);
	Sprites::instance()->getAnimation("Turret_Fire_Diagonal_Up_Right", &_animFireDiagonalUpRight[0]);
	Sprites::instance()->getAnimation("Turret_Fire_Diagonal_Up_Left", &_animFireDiagonalUpLeft[0]);
	Sprites::instance()->getAnimation("Turret_Fire_Diagonal_Down_Right", &_animFireDiagonalDownRight[0]);
	Sprites::instance()->getAnimation("Turret_Fire_Diagonal_Down_Left", &_animFireDiagonalDownLeft[0]);
	Sprites::instance()->getAnimation("Turret_Fire_Up", &_animFireUp[0]);
	Sprites::instance()->getAnimation("Turret_Fire_Down", &_animFireDown[0]);
	Sprites::instance()->getAnimation("Turret_Opening", &_animOpening);

	_mirror_x_dir = Direction::NONE;
}

void Turret::advance()
{
	Bill* player = Game::instance()->player();

	_prevViewDir = _viewDir;

	if (_life == 0)
	{
		Sounds::instance()->playSound("EnemyHit");
		setVisible(false);
		_dead = true;
		new Explosion(2, QPointF(x(), y()));
	}

	if ((player->x() - x() > -100 && player->x() - x() < 100)
		&& (player->y() - y() > -162 && player->y() - y() < 132.5) && _closed && !_opening)
	{
		_opening = true;
		schedule("opening_disable", 12, [this]()
			{
				_opening = false;
				_closed = false;

			});
	}


	if (player->x() - x() < -100 || player->x() - x() > 100)
	{
		_closed = true;
		_viewDir = Direction::NONE;
	}

	if (!_closed && !player->isDying())
	{
		if ((player->x() - x() > 0) && (player->y() - y() < TILE && player->y() - y() > -TILE))
		{
			fire(1.0 / 3, 0, 27, 13);
			_viewDir = Direction::RIGHT;
		}
		if ((player->x() - x() < 0) && (player->y() - y() < TILE && player->y() - y() > -TILE))
		{
			fire(-1.0 / 3, 0, 0, 13);
			_viewDir = Direction::LEFT;
		}
		if ((player->x() - x() > TILE) && player->y() - y() < -TILE)
		{
			fire(sqrt(2) / 2 / 3, -sqrt(2) / 2 / 3, 27, 7);
			_viewDir = Direction::UP_RIGHT;
		}
		if ((player->x() - x() < -TILE) && player->y() - y() < -TILE)
		{
			fire(-sqrt(2) / 2 / 3, -sqrt(2) / 2 / 3, 0, 7);
			_viewDir = Direction::UP_LEFT;
		}
		if ((player->x() - x() > TILE) && player->y() - y() > TILE)
		{
			fire(sqrt(2) / 2 / 3, sqrt(2) / 2 / 3, 27, 23);
			_viewDir = Direction::DOWN_RIGHT;
		}
		if ((player->x() - x() < -TILE) && player->y() - y() > TILE)
		{
			fire(-sqrt(2) / 2 / 3, sqrt(2) / 2 / 3, 0, 23);
			_viewDir = Direction::DOWN_LEFT;
		}
		if ((player->x() - x() < TILE && player->x() - x() > -TILE) && player->y() - y() < -TILE)
		{
			fire(0, -1.0 / 3, 13, 0);
			_viewDir = Direction::UP;
		}
		if ((player->x() - x() < TILE && player->x() - x() > -TILE) && player->y() - y() > TILE)
		{
			fire(0, 1.0 / 3, 13, 27);
			_viewDir = Direction::DOWN;
		}
	}
}

void Turret::animate()
{
	if (_opening)
		_animRect = &_animOpening;
	else if (_viewDir == Direction::RIGHT)
		_animRect = &_animFireRight[(FRAME_COUNT / 8) % 3];
	else if (_viewDir == Direction::LEFT)
		_animRect = &_animFireLeft[(FRAME_COUNT / 8) % 3];
	else if (_viewDir == Direction::UP_RIGHT)
		_animRect = &_animFireDiagonalUpRight[(FRAME_COUNT / 9) % 2];
	else if (_viewDir == Direction::UP_LEFT)
		_animRect = &_animFireDiagonalUpLeft[(FRAME_COUNT / 9) % 2];
	else if (_viewDir == Direction::DOWN_RIGHT)
		_animRect = &_animFireDiagonalDownRight[(FRAME_COUNT / 9) % 2];
	else if (_viewDir == Direction::DOWN_LEFT)
		_animRect = &_animFireDiagonalDownLeft[(FRAME_COUNT / 9) % 2];
	else if (_viewDir == Direction::UP)
		_animRect = &_animFireUp[(FRAME_COUNT / 9) % 2];
	else if (_viewDir == Direction::DOWN)
		_animRect = &_animFireDown[(FRAME_COUNT / 9) % 2];
	else
		_animRect = &_animClose[(FRAME_COUNT / 9) % 2];
}


void Turret::fire(double x_vel, double y_vel, double x_pos, double y_pos)
{
	if (_fire)
		return;

	_fire = true;
	_firing = true;

	new Bullet(QPoint(pos().x() + x_pos, pos().y() + y_pos), x_vel, y_vel, 1);

	schedule("fire_disable", 160, [this]()
		{
			_fire = false;

		});
}

bool Turret::hit(Object* what, Direction fromDir)
{
	Bill* player = Game::instance()->player();

	if (what->to<Bullet*>() && what->to<Bullet*>()->getOwner() == 0 && !_closed)
	{
		if (player->PowerUp() == 'M')
			_life = _life - 2;
		else _life--;
	}

	return true;
}