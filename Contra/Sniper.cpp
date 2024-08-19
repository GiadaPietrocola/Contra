#include "Sniper.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "Block.h"
#include "Bill.h"
#include "Bullet.h"
#include "Sounds.h"

using namespace Contra;

Sniper::Sniper(QPointF pos, bool final) : Enemy(pos, TILE, 2*TILE)
{
	_sprite = Sprites::instance()->getSprite("Enemies");
	_fire = false;
	_firing = false;
	_dying = false;
	_rising = false;
	_final = final;
	_viewDir = Direction::LEFT;
	_prevViewDir = Direction::LEFT;

	_collider.adjust(4, 15, -10, 0);

	Sprites::instance()->getAnimation("Sniper_Standing", &_animStand);
	Sprites::instance()->getAnimation("Sniper_Fire_Horizontal", &_animFireHorizontal[0]);
	Sprites::instance()->getAnimation("Sniper_Fire_Diagonal_Up", &_animFireDiagonalUp[0]);
	Sprites::instance()->getAnimation("Sniper_Fire_Diagonal_Down", &_animFireDiagonalDown[0]);
	Sprites::instance()->getAnimation("Sniper_Dying", &_animDying[0]);
	Sprites::instance()->getAnimation("Sniper_Hiding", &_animHiding);
	Sprites::instance()->getAnimation("Sniper_Rising", &_animRising);

}

void Sniper::advance()
{

	Bill* player = Game::instance()->player();

	_prevViewDir = _viewDir;

	if (((_final && (player->x() - x() > -100) || (!_final && (player->x() - x() > -124 && player->x() - x() < 135) && (player->y() - y() > -162 && player->y() - y() < 132.5)))) && !player->isDying() && !_dying)  {
		if(_final==true){
			_final = false;
			_rising = true;
			schedule("Not_Rising", 10, [this]()
				{
					_rising = false;

				});
		}

		Vec2D Direction = Vec2D(player->x() - x(), player->y() - y() + (50 - player->boundingRect().height()));
		Direction = Vec2D(player->x() - x(), player->y() - y() + (50 - player->boundingRect().height()));
		double distance;
		distance = dist(player);

		if (Direction.x> 0 && (Direction.y< TILE && Direction.y> -TILE)) {
			fire((Direction.x/ distance) / 3, (Direction.y/ distance) / 3, TILE, TILE - 10);
			_viewDir = Direction::RIGHT;
		}
		else if (Direction.x< 0 && (Direction.y< TILE && Direction.y> -TILE)) {
			fire((Direction.x/ distance) / 3, (Direction.y/ distance) / 3, 0, TILE - 10);
			_viewDir = Direction::LEFT;
		}
		else if (Direction.x>= 0 && Direction.y< 0) {
			fire((Direction.x/ distance) / 3, (Direction.y/ distance) / 3, TILE - 4, 2);
			_viewDir = Direction::UP_RIGHT;
		}
		else if (Direction.x< 0 && Direction.y< 0) {
			fire((Direction.x/ distance) / 3, (Direction.y/ distance) / 3, 2, 0);
			_viewDir = Direction::UP_LEFT;
		}
		else if (Direction.x>= 0 && Direction.y> 0) {
			fire((Direction.x/ distance) / 3, (Direction.y/ distance) / 3, TILE, TILE + 7);
			_viewDir = Direction::DOWN_RIGHT;
		}
		else if (Direction.x< 0 && Direction.y> 0) {
			fire((Direction.x/ distance) / 3, (Direction.y/ distance) / 3, -2, TILE + 7);
			_viewDir = Direction::DOWN_LEFT;
		}

	}
		
	DynamicObject::advance();
}

void Sniper::animate()
{
	if(_dying)
		_animRect = &_animDying[_animCounter/12];
	else if(_final)
		_animRect = &_animHiding;
	else if (_rising)
		_animRect = &_animRising;
	else if((_viewDir == Direction::RIGHT || _viewDir == Direction::LEFT) && !_firing)
		_animRect = &_animFireHorizontal[0];
	else if((_viewDir == Direction::RIGHT || _viewDir == Direction::LEFT))
		_animRect = &_animFireHorizontal[(FRAME_COUNT / 9) % 2];
	else if ((_viewDir == Direction::UP_RIGHT || _viewDir == Direction::UP_LEFT) && !_firing)
		_animRect = &_animFireDiagonalUp[0];
	else if ((_viewDir == Direction::UP_RIGHT || _viewDir == Direction::UP_LEFT))
		_animRect = &_animFireDiagonalUp[(FRAME_COUNT / 9) % 2];
	else if ((_viewDir == Direction::DOWN_RIGHT || _viewDir == Direction::DOWN_LEFT) && !_firing)
		_animRect = &_animFireDiagonalDown[0];
	else if ((_viewDir == Direction::DOWN_RIGHT || _viewDir == Direction::DOWN_LEFT))
		_animRect = &_animFireDiagonalDown[(FRAME_COUNT / 9) % 2];
		
	_animCounter++;
}

void Sniper::paint(QPainter* painter)
{
	if (_viewDir == Direction::LEFT || _viewDir == Direction::UP_LEFT || _viewDir == Direction::DOWN_LEFT)
	{
		painter->translate(_boundingRect.width(), 0);	
		painter->scale(-1, 1);							
	}

	Object::paint(painter);
}

void Sniper::fire(double x_vel, double y_vel, double x_pos, double y_pos)
{

	if (_fire)
		return;

	_fire = true;
	_firing = true;

	if (_countbullet > 3) {
		_firing = false;
		schedule("fire_disable", 50, [this]()
			{
				_fire = false;

			});
		_countbullet = 0;
	}
	else {
		_countbullet++;

		new Bullet(QPoint(pos().x() + x_pos, pos().y() + y_pos), x_vel, y_vel, 1);

	schedule("fire_disable", 10, [this]()
		{
			_fire = false;

		});
	}
}

bool Sniper::hit(Object* what, Direction fromDir)
{
	if (what->to<Bullet*>() && what->to<Bullet*>()->getOwner() == 0) {
		
		Sounds::instance()->playSound("EnemyHit");
		
		if (fromDir == Direction::RIGHT)
			Die(-1);
		else
			Die(1);
	}

	return true;
}

void Sniper::Die(int Direction)
{
	if (!_dying) {

		_dying = true;
		_collider.adjust(_collider.width(),_collider.height(),0,0);
		velAdd(Vec2Df(Direction*0.5, -3));
		_boundingRect.adjust(-3,0,3,0);
		_animCounter=0;

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