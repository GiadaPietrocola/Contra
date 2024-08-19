#include "Bullet.h"
#include "GameConfig.h"
#include "Game.h"
#include "Sprites.h"
#include <QPainter>
#include "Enemy.h"
#include "Soldier.h"
#include "Sniper.h"
#include "HidingSniper.h"
#include "Turret.h"
#include "Cannon.h"
#include "Bill.h"
#include "Sounds.h"
#include "FlyingPowerUp.h"
#include "TurretPowerUp.h"
#include "RepeaterCannon.h"
#include "Core.h"

using namespace Contra;


Bullet::Bullet(QPointF pos, double x_vel, double y_vel, bool owner) : DynamicObject(pos, 5, 5)
{

	_compenetrable = true;

	_owner = owner;
	_fire = true;

	defaultPhysics();

	_x_vel_max = x_vel * _x_vel_max;
	_y_vel_max = y_vel * _y_vel_max;


	_collider.adjust(1, 1, -1, -1);

	_sprite = Sprites::instance()->getSprite("Bullet");

	Sprites::instance()->getAnimation("Bullet_fire", &_animFire);
	Sprites::instance()->getAnimation("Bullet_fire_power_up", &_animFirePowerUp);

	_animRect = &_animFire;



}

void Bullet::defaultPhysics()
{
	_y_gravity = 0;
	_y_acc_jmp = 3;

	_y_vel_max = 3;
	_y_vel_min = 0.01;

	_x_vel_max = 3;
	_x_vel_min = 0.01;

	_x_acc = _x_vel_max;
	_x_dec_rel = _x_vel_max;
	_x_dec_skd = _x_vel_max;
}

void Bullet::advance()
{
	velAdd(Vec2Df(_x_acc, 0));
	velAdd(Vec2Df(0, _y_acc_jmp));

	DynamicObject::advance();

	if (x() > (Game::instance()->wiewRect().x() + Game::instance()->wiewRect().width()) ||
		x() < (Game::instance()->wiewRect().x()) ||
		y() > 225 ||
		y() < 0)
	{
		setVisible(false);
		_dead = true;
	}

}

void Bullet::animate()
{
	Bill* player = Game::instance()->player();

	if (player->PowerUp() == 'M' && _owner == 0)
		_animRect = &_animFirePowerUp;
}

bool Bullet::hit(Object* what, Direction fromDir)
{
	Bill* player = Game::instance()->player();

	if ((_owner == 0 && what->to<Enemy*>()) || (_owner == 1 && what->to<Bill*>() && !what->to<Bill*>()->invincible())
		|| (_owner == 0 && what->to<FlyingPowerUp*>() && what->to<FlyingPowerUp*>()->flying())
		|| (_owner == 0 && what->to<TurretPowerUp*>() && !what->to<TurretPowerUp*>()->Out()))
	{
		setVisible(false);
		_dead = true;

		if (what->to<Soldier*>())
			player->AddPoints(100);
		else if (what->to<Sniper*>())
			player->AddPoints(500);
		else if (what->to<HidingSniper*>())
			player->AddPoints(700);
		else if (what->to<Turret*>())
			player->AddPoints(300);
		else if (what->to<Cannon*>())
			player->AddPoints(500);
		else if (what->to<FlyingPowerUp*>() || what->to<TurretPowerUp*>())
			player->AddPoints(500);
		else if (what->to<RepeaterCannon*>())
			player->AddPoints(1000);
		else if (what->to<Core*>())
			player->AddPoints(10000);
	}


	return true;
}

bool Bullet::collidableWith(Object* obj, Direction dir)
{
	return false;

}