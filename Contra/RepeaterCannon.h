#pragma once

#include "Enemy.h"

namespace Contra
{
	class RepeaterCannon;
}

class Contra::RepeaterCannon : public Enemy
{
private:

	// state flags
	bool _fire;

	// animations
	QRect _animFire[4];

	int _side;
	int _life = 10;

public:

	RepeaterCannon(QPointF pos, int side);

	// implemented abstract methods
	virtual void animate() override;
	virtual std::string name() override { return "RepeaterCannon[" + std::to_string(_id) + "]"; }

	// reimplemented abstract methods
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual void advance() override;
};