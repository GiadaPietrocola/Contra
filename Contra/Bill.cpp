#include "Bill.h"
#include "Game.h"
#include "GameConfig.h"
#include "Block.h"
#include "Sprites.h"
#include "Bullet.h"
#include "Water.h"
#include "Bridge.h"
#include "Sounds.h"
#include <QPainter>
#include "Sniper.h"
#include "Soldier.h"
#include "HidingSniper.h"
#include "Elements.h"
#include "Bomb.h"
#include "FlyingPowerUp.h"
#include "TurretPowerUp.h"

using namespace Contra;

Bill::Bill(QPointF pos)
	: DynamicObject(pos, TILE, 2*TILE)
{
	_fire = false;
	_firing = false;
	_layingdown = false;
	_goingdown = false;
	_jumped = true;
	_passing = true;
	_inwater = false;
	_falled = true;
	_die = false;
	_dying = false;
	_invincible = false;
	_victory = false;
	_powerUp = 0;

	_score = 0;

	_viewDir = Direction::NONE;

	_prev_x_dir = Direction::RIGHT;

	_mirror_x_dir = Direction::LEFT;

	_sprite = Sprites::instance()->getSprite("Bill");

	_collider.adjust(4, 33, -10, -5);
	_boundingRect.adjust(0, TILE, 0,0);
	
	Sprites::instance()->getAnimation("Bill_stand", &_animStand);
	Sprites::instance()->getAnimation("Bill_walk", &_animWalk[0]);
	Sprites::instance()->getAnimation("Bill_jump", &_animJump[0]);
	Sprites::instance()->getAnimation("Bill_fall", &_animFall);
	Sprites::instance()->getAnimation("Bill_laying", &_animLaying);
	Sprites::instance()->getAnimation("Bill_water", &_animWater[0]);
	Sprites::instance()->getAnimation("Bill_fire_horizontal", &_animFireHorizontal[0]);
	Sprites::instance()->getAnimation("Bill_fire_horizontal_walk", &_animFireHorizontalWalk[0]);
	Sprites::instance()->getAnimation("Bill_fire_horizontal_water", &_animFireHorizontalWater[0]);
	Sprites::instance()->getAnimation("Bill_fire_vertical", &_animFireVertical[0]);
	Sprites::instance()->getAnimation("Bill_fire_vertical_water", &_animFireVerticalWater[0]);
	Sprites::instance()->getAnimation("Bill_fire_diagonal_up", &_animFireDiagonalUp[0]);
	Sprites::instance()->getAnimation("Bill_fire_diagonal_up_water", &_animFireDiagonalUpWater[0]);
	Sprites::instance()->getAnimation("Bill_fire_diagonal_down", &_animFireDiagonalDown[0]);
	Sprites::instance()->getAnimation("Bill_down_water", &_animDownWater);
	Sprites::instance()->getAnimation("Bill_dying", &_animDying[0]);
	Sprites::instance()->getAnimation("Bill_dead", &_animDead);
}

void Bill::advance()
{
	
		if (midair()) {
			if (_x_dir == Direction::RIGHT)
				velAdd(Vec2Df(_x_acc_jmp, 0));
			if (_x_dir == Direction::LEFT)
				velAdd(Vec2Df(-_x_acc_jmp, 0));

		}
		else {
			if (_x_dir == Direction::RIGHT)
				velAdd(Vec2Df(_x_acc, 0));
			else if (_x_dir == Direction::LEFT)
				velAdd(Vec2Df(-_x_acc, 0));
			else if (_x_dir == Direction::NONE)
				velAdd(Vec2Df(-_vel.versX() * _x_dec_rel, 0));

		}

	if (!_die) {
		if (_inwater) {

			if (_collider.height() == 35) {

				_collider.adjust(3, 21, 0, 0);
				_boundingRect.adjust(0, TILE, 0, 0);

				_falled = false;
				schedule("Bill_in_water", 12, [this]() {_falled = true; });


			}
			if (_layingdown) {

				velClipX(0);
				_mirror_x_dir = Direction::NONE;

				if (_collider.height() == 14) {
	
					_collider.adjust(0, 14, 0, 0);

				}
			}
			if (!_layingdown) {

				_mirror_x_dir = Direction::LEFT;

				if (_collider.height() == 0) {

					_collider.adjust(0, -14, 0, 0);

				}
			}
		}
		if (grounded() && _jumped) {

			if (_collider.height() == 12) {

				_collider.adjust(0, -18, 0, +5);
				_boundingRect.adjust(0, -TILE, 0, 0);
				setY(y() - 5);

			}
			_jumped = false;

		}
		if (_goingdown) {

			if (_collider.width() == 30) {

				_collider.adjust(-3, -21, -22, 0);
				_boundingRect.adjust(0, -TILE, -TILE, 0);

			}

			setPos(pos() + QPointF(0, 0.1));

			_goingdown = false;

		}
		if (_layingdown && !_inwater) {
			velClipX(0);

			if (_collider.width() == 11) {

				_collider.adjust(3, +21, +22, 0);
				_boundingRect.adjust(0, +TILE, +TILE, 0);

			}
		}
		if (!_layingdown) {

			if (_collider.width() == 30) {

				_collider.adjust(-3, -21, -22, 0);
				_boundingRect.adjust(0, -TILE, -TILE, 0);

			}
		}
	}

	if (y() > 220 && !_die) {

		Die();
		_lifes--;

	}
		
	if (_powerUp == 'B' && !_invincible) {

		_invincible = true;
		schedule("End_power_up", 6 * 60, [this]()
			{
				_invincible = false;
				_powerUp = 0;
			});
	}

	DynamicObject::advance();

}

void Bill::animate()
{

	if(_dying)
		_animRect = &_animDead;
	else if (_die)
		_animRect = &_animDying[_animCounter/10];
	else if (_inwater && _layingdown) 
		_animRect = &_animDownWater;
	else if (_inwater && _firing && _viewDir == Direction::UP) 
		_animRect = &_animFireVerticalWater[(FRAME_COUNT / 20) % 2];
	else if(_inwater && _firing && (_viewDir == Direction::UP_RIGHT || _viewDir == Direction::UP_LEFT)) 
		_animRect = &_animFireDiagonalUpWater[(FRAME_COUNT / 20) % 2];
	else if (_inwater && _firing) 
		_animRect = &_animFireHorizontalWater[(FRAME_COUNT / 20) % 2];
	else if (_inwater) 
		_animRect = &_animWater[((FRAME_COUNT / 20) % (1+_falled)) + _falled];
	else if (falling() && !_jumped) 
		_animRect = &_animFall;
	else if (midair())
			_animRect = &_animJump[(FRAME_COUNT / 7) % 2];
	else if (_layingdown)
		_animRect = &_animLaying;
	else if (_firing && _viewDir == Direction::NONE && _vel.x==0)
		_animRect = &_animFireHorizontal[(FRAME_COUNT / 7) % 2];
	else if(_firing && _viewDir == Direction::NONE)
		_animRect = &_animFireHorizontalWalk[(FRAME_COUNT / 7) % 2];
	else if (_firing && _viewDir == Direction::UP)
		_animRect = &_animFireVertical[(FRAME_COUNT / 7) % 2];
	else if (_viewDir == Direction::UP_RIGHT || _viewDir == Direction::UP_LEFT)
		_animRect = &_animFireDiagonalUp[(FRAME_COUNT / 7) % 3];
	else if (_viewDir == Direction::DOWN_RIGHT || _viewDir == Direction::DOWN_LEFT)
		_animRect = &_animFireDiagonalDown[(FRAME_COUNT / 7) % 3];
	else if (_viewDir == Direction::UP)
		_animRect = &_animFireVertical[0];
	else {
		if (_vel.x == 0)
			_animRect = &_animStand;
		else
			_animRect = &_animWalk[(FRAME_COUNT / 7) % 6];
	}

	if (_invincible && (FRAME_COUNT / 4) % 2)
		_animRect = 0;

	_animCounter++;
}

bool Bill::collidableWith(Object* obj, Direction dir)
{
	if (obj->to<Block*>() && _inwater && (dir==Direction::LEFT || dir==Direction::RIGHT))
		return true;
	else if (obj->to<Block*>() && dir != Direction::DOWN)
		return false;
	else
		return true;
}

bool Bill::hit(Object* what, Direction fromDir)
{
	if (what->to<Block*>() && _inwater) {

		_inwater = false;

		if (_collider.height() == 14) {

			if (_x_dir == Direction::RIGHT) {
				setPos(QPoint(x(),y()+25) + QPointF(0.2 * TILE, -1.01 * TILE));
			}

			else if (_x_dir == Direction::LEFT) {
				setPos(QPoint(x(), y() + 25) + QPointF(-0.2 * TILE, -1.01 * TILE));
			}

			_collider.adjust(-3, -21, 0, 0);
			_boundingRect.adjust(0, -TILE, 0, 0);

			}
		}

	if (what->to<Block*>() && !what->to<Block*>()->passable()){
		_passing = false;
	}
	else if (what->to<Block*>() && what->to<Block*>()->passable()) {
		_passing = true;
	}
	if (what->to<Water*>() && !_die) {
		_inwater = true;
		_passing = false;
	}
	if (what->to<Bridge*>()) {
		what->to<Bridge*>()->explode();
	}
	if (what->to<Bridge*>() && _inwater) {
		what->to<Bridge*>()->explode();
	}

	if (((what->to<Bullet*>() && what->to<Bullet*>()->getOwner() == 1) || what->to<Sniper*>() || what->to<Soldier*>() || what->to<Bomb*>() ||
		(what->to<HidingSniper*>() && !what->to<HidingSniper*>()->hiding())) && !_die && !_invincible) {
		
		Sounds::instance()->playSound("Death");

		if (fromDir == Direction::RIGHT) {
			Die();
			_x_dir = Direction::LEFT;
			
		}	
		else{
			Die();
			_x_dir = Direction::RIGHT;
		}

		_lifes--;
	
	}

	if (what->to<Water*>()  && _die) {
		setVisible(false);

	}
	if (what->to<FlyingPowerUp*>() && !what->to<FlyingPowerUp*>()->flying() && !_die) {
		_powerUp = what->to<FlyingPowerUp*>()->typePowerUp();
		AddPoints(1000);
		Sounds::instance()->playSound("PowerUp");
	}
	if (what->to<TurretPowerUp*>() && what->to<TurretPowerUp*>()->Out() && !_die) {
		_powerUp = what->to<TurretPowerUp*>()->typePowerUp();
		AddPoints(1000);
		Sounds::instance()->playSound("PowerUp");
	}
	return true;


}

void Bill::jump()
{

	if (!midair() && !_goingdown && !_inwater && !_jumped && !_die)
	{
		velAdd(Vec2Df(0, -_y_acc_jmp));
		setY(y() + 5);
		_collider.adjust(0, 18, 0, -5);
		_boundingRect.adjust(0, +TILE, 0, 0);

		_jumped = true;

	}
	
}

void Bill::liedown(bool on)
{
	if (on == true && !midair() && !_jumped && !_goingdown)
		_layingdown = on;
	else if (on == false)
		_layingdown = on;

}

void Bill::godown()
{
	if (_goingdown)
		return;

	if (_passing && _layingdown) {
		_goingdown = true; 
		_layingdown = false;
	}
	
}

void Bill::fire()
{
	
	if (_fire || _die)
		return;

	_fire = true;
	
	if (_countbullet > 3) {
		_firing = false;
		if (_powerUp=='R') {
			schedule("fire_disable", 10, [this]()
				{
					_fire = false;

				});
		}
		else if (_powerUp == 'M') {
			_fire = false;
		}
		else {
			schedule("fire_disable", 15, [this]()
				{
					_fire = false;

				});
		}

		_countbullet = 0;
	}
	else{

		_firing = true;
		_countbullet++;

		Sounds::instance()->playSound("Rifle");

		if (_viewDir == Direction::NONE) {
			if (_layingdown) {
				if (_x_dir == Direction::RIGHT || (_x_dir == Direction::NONE && _prev_x_dir == Direction::RIGHT))
					new Bullet(QPoint(pos().x() + 40, pos().y() + 36), 1, 0, 0);
				else if (_x_dir == Direction::LEFT || (_x_dir == Direction::NONE && _prev_x_dir == Direction::LEFT))
					new Bullet(QPoint(pos().x()+7, pos().y() + 36), -1, 0, 0);
			}
			else if (_inwater) {
				if (_x_dir == Direction::RIGHT || (_x_dir == Direction::NONE && _prev_x_dir == Direction::RIGHT))
					new Bullet(QPoint(pos().x()-2 + TILE, pos().y() + 43 ),1,0, 0);
				else if (_x_dir == Direction::LEFT || (_x_dir == Direction::NONE && _prev_x_dir == Direction::LEFT))
					new Bullet(QPoint(pos().x()-2, pos().y() + 43 ), -1, 0, 0);
			}
			else
				if (_x_dir == Direction::RIGHT || (_x_dir == Direction::NONE && _prev_x_dir == Direction::RIGHT))
					new Bullet(QPoint(pos().x() + TILE -4, pos().y() + TILE), 1, 0, 0);
				else if (_x_dir == Direction::LEFT || (_x_dir == Direction::NONE && _prev_x_dir == Direction::LEFT))
					new Bullet(QPoint(pos().x(), pos().y() + TILE), -1, 0, 0);


		}
		else if (_viewDir == Direction::UP && !_inwater)
			new Bullet(QPoint(pos().x() + (TILE / 2) -1, pos().y()+2), 0,-1, 0);
		else if (_viewDir == Direction::UP_RIGHT && !_inwater)
			new Bullet(QPoint(pos().x() + TILE-4, pos().y()+10), sqrt(2)/2, -sqrt(2) / 2, 0);
		else if (_viewDir == Direction::UP_LEFT && !_inwater)
			new Bullet(QPoint(pos().x()+2, pos().y() + 12), -sqrt(2) / 2,- sqrt(2) / 2, 0);
		else if (_viewDir == Direction::DOWN_RIGHT && !_inwater)
			new Bullet(QPoint(pos().x() + TILE-2, pos().y() + TILE+8), sqrt(2) / 2, +sqrt(2) / 2, 0);
		else if (_viewDir == Direction::DOWN_LEFT && !_inwater)
			new Bullet(QPoint(pos().x(), pos().y() + TILE+8), -sqrt(2) / 2, +sqrt(2) / 2, 0);
		else if (_viewDir == Direction::UP_RIGHT)
			new Bullet(QPoint(pos().x() + TILE - 4, pos().y() + 31), sqrt(2) / 2, -sqrt(2) / 2, 0);
		else if (_viewDir == Direction::UP_LEFT)
			new Bullet(QPoint(pos().x() + 2, pos().y() + 31), -sqrt(2) / 2, -sqrt(2) / 2, 0);
		else if (_viewDir == Direction::UP)
			new Bullet(QPoint(pos().x() + (TILE / 2) , pos().y() + 20), 0, -1, 0);
	
		if (_powerUp == 'R') {
			schedule("fire_disable", 3, [this]()
				{
					_fire = false;
					_firing = false;
				});
		}
		else if (_powerUp == 'M') {
			schedule("fire_disable", 8, [this]()
				{
					_fire = false;
					_firing = false;
				});
		}
		else
			schedule("fire_disable", 5, [this]()
				{
					_fire = false;
					_firing = false;
				});

		}

}

void Bill::viewDirection(Direction View)
{
	_viewDir = View;
}

void Bill::Die() {

	if (_die)
		return;

	_die = true;
	_layingdown = false;
	_inwater = false;
	_powerUp = 0;

	_animCounter = 0;

	if(_collider.height()==35){
		_collider.adjust(0, 18, 0, 0);
		_boundingRect.adjust(0, +TILE, 0, 0);
	}
	if (_collider.width() == 30) {
		_collider.adjust(-3, -3, -22, 0);
		_boundingRect.adjust(0, 0, -TILE, 0);
	}
	if (_collider.height() == 14) {
		_collider.adjust(-3, -3, 0, 0);
	}
	if (_collider.height() == 12) {
		_collider.adjust(0, 0, 0, 5);
	}

	velClipX(0);
	velClipY(0);

	velAdd(Vec2Df(0, -3));

	schedule("Adjust", 40, [this]()
		{
			_dying = true;

			if (_collider.height() == 17) {

				_collider.adjust(0, 0, +22, 0);
				_boundingRect.adjust(0, 0, +TILE, 0);
			}
		});
	
	schedule("Not_Visible", 120, [this]()
		{
			setVisible(false);

			if (_lifes == 0) 
				_dead = true;
				

		});

	schedule("Respawn", 5 * 60, [this]()
		{
			_collider.adjust(0, 0, -22, -5);
			_boundingRect.adjust(0, 0, -TILE, 0);
			setPos(Game::instance()->wiewRect().x()+2*TILE, 2);
			setVisible(true);
			_jumped = true;
			_dying = false;
			_die = false;
			_invincible = true;


			schedule("Not_invincible", 3 * 60, [this]()
				{
					_invincible = false;

				});
		});
}

void Bill::AddPoints(int points) {
	_score += points;
}
