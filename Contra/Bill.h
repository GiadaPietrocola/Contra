#pragma once

#include "DynamicObject.h"

namespace Contra
{
	class Bill;
}

class Contra::Bill : public DynamicObject
{
private:

	// state flags
	bool _fire;
	bool _firing;
	bool _layingdown;
	bool _goingdown;
	bool _jumped;
	bool _passing;
	bool _inwater;
	bool _falled;
	bool _dying;
	bool _die;
	bool _invincible;
	bool _victory;

	// animations
	QRect _animStand;
	QRect _animWalk[6];
	QRect _animJump[4];
	QRect _animFall;
	QRect _animLaying;
	QRect _animWater[3];
	QRect _animFireHorizontal[2];
	QRect _animFireHorizontalWalk[3];
	QRect _animFireHorizontalWater[2];
	QRect _animFireVertical[2];
	QRect _animFireVerticalWater[2];
	QRect _animFireDiagonalUp[3];
	QRect _animFireDiagonalUpWater[2];
	QRect _animFireDiagonalDown[3];
	QRect _animDownWater;
	QRect _animDying[4];
	QRect _animDead;

	Direction _viewDir;

	int	_countbullet = 0;
	int _animCounter = 0;
	int _lifes = 3;
	int _score;

	// Power Up type
	char _powerUp;
public:

	Bill(QPointF pos);

	// implemented abstract methods
	virtual void animate() override;
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual std::string name() override { return "Player"; }

	// reimplemented methods
	virtual void advance() override;
	virtual bool collidableWith(Object* obj, Direction dir) override;

	// player actions
	virtual void fire();
	virtual void jump() override;
	virtual void liedown(bool on = true);
	virtual void godown();
	virtual void viewDirection(Direction view = Direction::NONE);
	virtual void Die();
	virtual void AddPoints(int points);
	virtual void SetInvincible() { _invincible = !_invincible; }
	virtual void victory() { _victory = true; }

	// getters
	virtual int Score() const { return _score; }
	virtual bool getVictory() { return _victory; };
	virtual bool invincible() const { return _invincible; }
	virtual bool isDying() const { return _die; }
	virtual char PowerUp() const { return _powerUp; }
	virtual int lifes() const { return _lifes; }
	virtual bool hiding() { return (_inwater && _layingdown); }
};