#pragma once

#include "DynamicObject.h"
//#include "Enemy.h"

namespace Contra
{
	class Bullet;
}

class Contra::Bullet : public DynamicObject
{
private:

	// state flags
	bool _fire;

	// who shot the bullet
	bool _owner;

	// animations
	QRect _animFire;
	QRect _animFirePowerUp;

	Direction _y_dir;

public:

	Bullet(QPointF pos, double x_vel, double y_vel, bool owner);

	// implemented abstract methods
	virtual void animate() override;
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual std::string name() override { return "Bullet[" + std::to_string(_id) + "]"; }

	// reimplemented methods
	virtual void advance() override;
	virtual void defaultPhysics() override;
	virtual bool collidableWith(Object* obj, Direction dir) override;

	// getter
	bool getOwner() { return _owner; }
};
