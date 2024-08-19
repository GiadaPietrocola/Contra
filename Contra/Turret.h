#pragma once

#include "Enemy.h"

namespace Contra
{
	class Turret;
}

class Contra::Turret : public Enemy
{
private:

	// state flags
	bool _fire;
	bool _firing;
	bool _closed;
	bool _opening;

	// animations
	QRect _animClose[3];
	QRect _animOpening;
	QRect _animFireRight[3];
	QRect _animFireLeft[3];
	QRect _animFireDiagonalUpRight[3];
	QRect _animFireDiagonalUpLeft[3];
	QRect _animFireDiagonalDownRight[3];
	QRect _animFireDiagonalDownLeft[3];
	QRect _animFireUp[3];
	QRect _animFireDown[3];

	Direction _viewDir;
	Direction _prevViewDir;

	int _countbullet = 0;
	int _life = 8;

public:

	Turret(QPointF pos);

	// implemented abstract methods
	virtual void animate() override;
	virtual std::string name() override { return "Turret[" + std::to_string(_id) + "]"; }

	// reimplemented abstract methods
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual void advance() override;

	// actions
	virtual void fire(double x_vel, double y_vel, double x_pos, double y_pos);
};