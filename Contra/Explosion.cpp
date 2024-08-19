#include "Explosion.h"
#include "Sounds.h"
#include "Game.h"
#include "GameConfig.h"
#include "Sprites.h"

using namespace Contra;

Explosion::Explosion(int type, QPointF pos) : Object(pos, 45, 45) {

	_sprite = Sprites::instance()->getSprite("Explosion");

	Sprites::instance()->getAnimation("Explosion_Bridge", &_animExplosionBridge[0]);
	Sprites::instance()->getAnimation("Explosion", &_animExplosion[0]);

	_compenetrable = true;
	_exploded = true;

	_type = type;
}

void Explosion::animate()
{
	if (_type == 1) {
		_animRect = &_animExplosionBridge[_animCounter/10];
	}
	if (_type == 2) {
		_animRect = &_animExplosion[_animCounter/10];
	}

	_animCounter++;
}

void Explosion::advance() {

	if(_type==1 && _exploded){

		Sounds::instance()->playSound("BridgeExplosion");
		_exploded = false;

		schedule("End", 50, [this]()
			{
				setVisible(false);
			});
	}

	if (_type == 2 && _exploded) {

		_exploded = false;

		schedule("End", 50, [this]()
			{
				setVisible(false);
			});
	}
}