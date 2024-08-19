#pragma once

#include "Enemy.h"

namespace Contra
{
	class Sniper;
}

class Contra::Sniper : public Enemy
{
private:

	// state flags
	bool _fire;
	bool _firing;
	bool _dying;
	bool _final;
	bool _rising;

	// animations
	QRect _animStand;
	QRect _animFireHorizontal[2];
	QRect _animDying[4];
	QRect _animFireDiagonalUp[2];
	QRect _animFireDiagonalDown[2];
	QRect _animHiding;
	QRect _animRising;

	Direction _viewDir;
	Direction _prevViewDir;

	int _countbullet = 0;
	int _animCounter = 0;

public:

	Sniper(QPointF pos, bool final = false);

	// implemented abstract methods
	virtual void animate() override;
	virtual std::string name() override { return "Sniper[" + std::to_string(_id) + "]"; }

	// reimplemented abstract methods
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual void advance() override;
	virtual void paint(QPainter* painter) override;
	
	// actions
	virtual void fire(double x_vel, double y_vel, double x_pos, double y_pos);
	void Die(int Direction);
	

	};