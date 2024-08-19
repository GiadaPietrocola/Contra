#include "Enemy.h"
#include "GameConfig.h"
#include "Bill.h"

using namespace Contra;

Enemy::Enemy(QPointF pos, double width, double height) : DynamicObject(pos, width, height)
{
	_mirror_x_dir = Direction::RIGHT;
}

bool Enemy::hit(Object* what, Direction fromDir)
{
	if (what->to<Bill*>())
	{
		return true;
	}

	return false;
}