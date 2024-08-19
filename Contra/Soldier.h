#pragma once

#include "Enemy.h"

namespace Contra
{
	class Soldier;
}

class Contra::Soldier : public Enemy
{
private:

	// state flags
	bool _choice = true;
	bool _dying;
	bool _inWater;
	bool _notActive;

	// animations
	QRect _animWalk[5];
	QRect _animJump;
	QRect _animDying[4];
	QRect _animWater[2];

	double _y_start;
	double _x_start;

	int _animCounter = 0;

public:

	Soldier(QPointF pos);

	// implemented abstract methods
	virtual void animate() override;
	virtual std::string name() override { return "Soldier[" + std::to_string(_id) + "]"; }

	// reimplemented abstract methods
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual void advance() override;

	// actions
	void Die(int Direction);
};