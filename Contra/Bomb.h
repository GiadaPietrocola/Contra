#pragma once

#include "DynamicObject.h"
//#include "Enemy.h"

namespace Contra
{
	class Bomb;
}

class Contra::Bomb : public DynamicObject
{
private:

	// animations
	QRect _animFire;


public:

	Bomb(QPointF pos);

	// implemented abstract methods
	virtual void animate() override {};
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual std::string name() override { return "Bomb[" + std::to_string(_id) + "]"; }

	// reimplemented methods
	virtual void advance() override;
	virtual bool collidableWith(Object* obj, Direction dir) override { return false; }

};
