#include "RepeaterCannon.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "Block.h"
#include "Bill.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Bomb.h"
#include "Sounds.h"

using namespace Contra;

RepeaterCannon::RepeaterCannon(QPointF pos,int side) : Enemy(pos, 12, 8)
{
	_sprite = Sprites::instance()->getSprite("FinalBoss");
	_fire = false;
	_side = side;

	Sprites::instance()->getAnimation("Repeater_Cannon_Fire", &_animFire[0]);

	_mirror_x_dir = Direction::NONE;

}

void RepeaterCannon::advance()
{

	Bill* player = Game::instance()->player();

	if (_life == 0) {

		setVisible(false);
		_dead = true;
		new Explosion(2, QPointF(x() - 12, y() - 12));
		Sounds::instance()->playSound("CannonExplosion");
	}

	if ((player->x() - x() > -200)) {

		if (!_fire) {

			_fire = true;

			if (_side == 0) {

				new Bomb(QPoint(x()-4, y()-2));
				Sounds::instance()->playSound("Bomb");
				schedule("End_bomb", 60, [this]()
					{
						_fire = false;
					});
			}
			else {

				schedule("New_Bomb", 30, [this]()
					{
						new Bomb(QPoint(x()-4,y()-2));
						Sounds::instance()->playSound("Bomb");
					});

				schedule("End_bomb", 60, [this]()
					{
						_fire = false;
					});
			}
		}
	}
}

void RepeaterCannon::animate()
{
	if(_side==0){
		_animRect = &_animFire[(FRAME_COUNT / 15) % 4];
	}
	else
		_animRect = &_animFire[((FRAME_COUNT+30) / 15) % 4];
}


bool RepeaterCannon::hit(Object* what, Direction fromDir)
{
	Bill* player = Game::instance()->player();

	if (what->to<Bullet*>() && what->to<Bullet*>()->getOwner() == 0) {

		if (player->PowerUp() == 'M')
			_life = _life - 2;
		else _life--;
	}

	return true;
}