#pragma once

#include "Enemy.h"

namespace Contra
{
	class HidingSniper;
}

class Contra::HidingSniper : public Enemy
{
private:

	// state flags
	bool _fire;
	bool _hiding;
	bool _rising;
	bool _out;
	bool _dying;

	// animations
	QRect _animHiding;
	QRect _animFireHorizontal;
	QRect _animDying[4];

	Direction _viewDir;

	int _countbullet = 0;
	int _animCounter = 0;

public:

	HidingSniper(QPointF pos);

	// implemented abstract methods
	virtual void animate() override;
	virtual std::string name() override { return "HidingSniper[" + std::to_string(_id) + "]"; }

	// reimplemented abstract methods
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual void advance() override;
	virtual void paint(QPainter* painter) override;

	// actions
	virtual void fire(double x_vel, double y_vel, double x_pos, double y_pos);
	virtual void Die(int Direction);
	
	// getters
	virtual bool hiding() const { return _hiding; }
};