#include "Soldier.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "Block.h"
#include "Bridge.h"
#include "Bill.h"
#include "Bullet.h"
#include "Water.h"
#include "Sounds.h"

using namespace Contra;

Soldier::Soldier(QPointF pos) : Enemy(pos, TILE, 2 * TILE)
{
	_dying = false;
	_inWater = false;
	_notActive = true;

	_animCounter = 0;

	_sprite = Sprites::instance()->getSprite("Enemies");

	Sprites::instance()->getAnimation("Soldier_Walking", &_animWalk[0]);
	Sprites::instance()->getAnimation("Soldier_Jump", &_animJump);
	Sprites::instance()->getAnimation("Soldier_Dying", &_animDying[0]);
	Sprites::instance()->getAnimation("Soldier_Water", &_animWater[0]);

	_collider.adjust(4, 18, -8, 0);

	_x_dir = Direction::LEFT;

	_mirror_x_dir = Direction::LEFT;

	_y_acc_jmp = 2.7;

	_y_start = pos.y();
	_x_start = pos.x();


	setVisible(false);
}

void Soldier::advance()
{

	Bill* player = Game::instance()->player();

	if (isVisible() && !_dying && !_inWater)
	{
		if (_x_dir == Direction::RIGHT)
			velAdd(Vec2Df(_x_acc, 0));
		else if (_x_dir == Direction::LEFT)
			velAdd(Vec2Df(-_x_acc, 0));

	}

	if (isVisible())
		DynamicObject::advance();



	if (x() > (Game::instance()->wiewRect().x()) && x() < (Game::instance()->wiewRect().x() + Game::instance()->wiewRect().width())
		&& !_inWater && _notActive)
	{
		setVisible(true);
		_notActive = false;
	}

	if (x() < (Game::instance()->wiewRect().x()) && !_notActive && !_inWater)
	{
		_notActive = true;
		setVisible(false);
		if (player->x() < _x_start)
		{
			schedule("Respawn", 3 * 60, [this]()
				{
					setPos((Game::instance()->wiewRect().x() + Game::instance()->wiewRect().width()), _y_start);
					setVisible(true);
					_notActive = false;
				});
		}
		else
			_dead = true;
	}
	else if (x() > (Game::instance()->wiewRect().x() + Game::instance()->wiewRect().width()) && isVisible())
		_x_dir = Direction::LEFT;

}

bool Soldier::hit(Object* what, Direction fromDir)
{
	Bill* player = Game::instance()->player();

	srand(time(0) + _id);
	_choice = (rand() % 2);

	int num_block = 0;
	QRectF curRect = qsceneCollider();
	curRect.adjust(-5, 27, 5, 5);



	if (((what->to<Block*>() || what->to<Bridge*>()) && what->x() > x()))
	{

		QList<QGraphicsItem*> items_in_rect = Game::instance()->world()->items(curRect);
		for (auto item : items_in_rect)
		{
			Object* obj = dynamic_cast<Object*>(item);
			if (obj->to<Block*>() || obj->to<Bridge*>())
				num_block++;

		}


		if (num_block == 1)
		{
			if (_choice == 0)
				_x_dir = Direction::RIGHT;
			else if (_choice == 1)
				jump();
		}

	}
	else if (what->to<Block*>() && (what->x() + what->collider().width()) < x())
	{
		_x_dir = Direction::LEFT;
	}

	if (what->to<Bullet*>() && what->to<Bullet*>()->getOwner() == 0)
	{
		Sounds::instance()->playSound("EnemyHit");

		if (fromDir == Direction::RIGHT)
			Die(-1);
		else
			Die(1);
	}
	if (what->to<Water*>() && !_inWater)
	{
		_animCounter = 0;
		_inWater = true;
		velClipX(0);
		velClipY(0);


		schedule("Not_Visible", 14, [this]()
			{
				setVisible(false);


			});

		if (player->x() < _x_start)
		{
			schedule("Respawn_water", 3 * 60, [this]()
				{
					setPos((Game::instance()->wiewRect().x() + Game::instance()->wiewRect().width()), _y_start);
					setVisible(true);
					_inWater = false;
				});
		}
		else
		{
			schedule("Dead", 14, [this]()
				{
					_dead = true;


				});
		}


	}


	return true;
}


void Soldier::animate()
{
	if (_inWater)
		_animRect = &_animWater[_animCounter / 7];
	else if (_dying)
		_animRect = &_animDying[_animCounter / 12];
	else if (midair())
		_animRect = &_animJump;
	else _animRect = &_animWalk[(FRAME_COUNT / 7) % 5];

	_animCounter++;
}

void Soldier::Die(int Direction)
{
	if (!_dying)
	{

		_dying = true;
		velAdd(Vec2Df(Direction * 1.5, -3));
		_collider.adjust(_collider.width(), _collider.height(), 0, 0);
		_boundingRect.adjust(-3, 0, 3, 0);
		_animCounter = 0;

		schedule("Soldier_Die_1", 12, [this]()
			{
				_y_gravity = 0;
				velClipX(0);
				velClipY(0);
			});

		schedule("Soldier_Die_2", 48, [this]()
			{
				setVisible(false);
				_dead = true;
			});
	}
}