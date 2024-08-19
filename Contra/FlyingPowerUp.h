#pragma once

#include "DynamicObject.h"

namespace Contra
{
	class FlyingPowerUp;
}

class Contra::FlyingPowerUp : public DynamicObject
{
private:

	// state flags
	bool _flying;

	// animations
	QRect _animFlying;
	QRect _animPowerUp[3];

	// type of Power Up
	char _type;

public:

	FlyingPowerUp(QPointF pos, char type);

	// implemented abstract methods
	virtual void animate() override;
	virtual std::string name() override { return "FlyingPowerUp[" + std::to_string(_id) + "]"; }

	// reimplemented abstract methods
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual void advance() override;

	// getters
	virtual bool flying() const { return _flying; }
	virtual char typePowerUp() const { return _type; }
};