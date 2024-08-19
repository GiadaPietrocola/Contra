#include "Cannon.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "Block.h"
#include "Bill.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Sounds.h"

using namespace Contra;

Cannon::Cannon(QPointF pos)	: Enemy(pos, TILE + 7.5, TILE + 7.5)
{
	_sprite = Sprites::instance()->getSprite("Towers");
	_fire = false;
	_firing = false;
	_closed = true;
	_opening = 0;
	_viewDir = Direction::LEFT;
	_mirror_x_dir = Direction::NONE;

	Sprites::instance()->getAnimation("Cannon_Fire_Left", &_animFireLeft[0]);
	Sprites::instance()->getAnimation("Cannon_Fire_Diagonal_Up_Left", &_animFireDiagonalUpLeft[0]);
	Sprites::instance()->getAnimation("Cannon_Fire_Up", &_animFireUp[0]);
	Sprites::instance()->getAnimation("Cannon_Opening_1", &_animOpening[0][0]);
	Sprites::instance()->getAnimation("Cannon_Opening_2", &_animOpening[1][0]);
	Sprites::instance()->getAnimation("Cannon_Closed", &_animClosed);

	_collider.adjust(0, TILE + 7.5, 0, 0);
}

void Cannon::advance()
{
	Bill* player = Game::instance()->player();

	if (_life == 0) {

		Sounds::instance()->playSound("EnemyHit");
		setVisible(false);
		_dead = true;
		new Explosion(2, QPointF(x(), y()));
	}

	Vec2D Direction = Vec2D(player->x() - x(), player->y() - y() + (50 - player->boundingRect().height()));
	Direction = Vec2D(player->x() - x(), player->y() - y() + (50 - player->boundingRect().height()));

	if ((Direction.x > -100 && Direction.x < 100) && (Direction.y > -162 && Direction.y < 132.5) && _closed && _opening==0) {
		
		_collider.adjust(0, -15, 0, 0);
		_opening++;

		schedule("rising", 30, [this]()
			{
				_collider.adjust(0, -8, 0, 0);
				_opening++;

				schedule("opening_disable", 30, [this]()
					{
						_opening++;
						_collider.adjust(0, -9.5, 0, 0);
						_closed = false;

					});
			});
	}

	if ((Direction.x > -100 && Direction.x < 100) && (Direction.y > -162 && Direction.y < 132.5) && _closed) {

		_closed = false;
	}

	if ((Direction.x < -250 || Direction.x > 150) && !_closed) {

		_closed = true;
		_viewDir = Direction::NONE;
	}

	if (!_closed && _opening == 3 && !player->isDying()) {

		if ((Direction.x < 0) && (Direction.y < TILE && Direction.y > -TILE)) {

			fire(-1.0 / 3, 0, -2, 13);
			_viewDir = Direction::LEFT;
		}
		else if ((Direction.x < -TILE) && Direction.y < -TILE) {
			
			fire(-sqrt(2) / 2 / 3, -sqrt(2) / 2 / 3, -2, 7);
			_viewDir = Direction::UP_LEFT;
		}
		else if ((Direction.x < 0) && Direction.y < -TILE) {

			fire(-0.382 / 3, -0.924 / 3, 5, -2);
			_viewDir = Direction::UP;
		}
	}
}

void Cannon::animate()
{
	if (_closed)
		_animRect = &_animClosed;
	else if (_opening>0 && _opening<3)
		_animRect = &_animOpening[_opening - 1][(FRAME_COUNT / 8) % 3];
	else if (_viewDir == Direction::LEFT)
		_animRect = &_animFireLeft[(FRAME_COUNT / 8) % 3];
	else if (_viewDir == Direction::UP_LEFT)
		_animRect = &_animFireDiagonalUpLeft[(FRAME_COUNT / 9) % 3];
	else if (_viewDir == Direction::UP)
		_animRect = &_animFireUp[(FRAME_COUNT / 9) % 3];
}


void Cannon::fire(double x_vel, double y_vel, double x_pos, double y_pos)
{

	if (_fire)
		return;

	_fire = true;

	if (_countbullet > 2) {
		_firing = false;

		schedule("fire_disable", 100, [this]()
			{
				_fire = false;

			});

		_countbullet = 0;
	}
	else {
		_countbullet++;
		_firing = true;

		new Bullet(QPoint(pos().x() + x_pos, pos().y() + y_pos), x_vel, y_vel, 1);	

	schedule("fire_disable", 15, [this]()
		{
			_fire = false;
			_firing = false;
		});
	}	

}

bool Cannon::hit(Object* what, Direction fromDir)
{
	Bill* player = Game::instance()->player();

	if (what->to<Bullet*>() && what->to<Bullet*>()->getOwner() == 0 && !_closed) {

		if (player->PowerUp() == 'M')
			_life = _life - 2;
		else _life--;

	}

	return true;
}