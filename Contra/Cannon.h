#pragma once

#include "Enemy.h"

namespace Contra
{
	class Cannon;
}

class Contra::Cannon : public Enemy
{
private:

	// state flags
	bool _fire;
	bool _firing;
	bool _closed;
	int _opening;

	// animations
	QRect _animClosed;
	QRect _animOpening[2][3];
	QRect _animFireLeft[3];
	QRect _animFireDiagonalUpLeft[3];
	QRect _animFireUp[3];

	Direction _viewDir;

	int _countbullet = 0;
	int _life = 8;

public:

	Cannon(QPointF pos);

	// implemented abstract methods
	virtual void animate() override;
	virtual std::string name() override { return "Cannon[" + std::to_string(_id) + "]"; }

	// reimplemented abstract methods
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual void advance() override;
	virtual void fire(double x_vel, double y_vel, double x_pos, double y_pos);
};