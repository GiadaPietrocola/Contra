#pragma once

#include "DynamicObject.h"

namespace Contra
{
	class TurretPowerUp;
}

class Contra::TurretPowerUp : public DynamicObject
{
private:

	// state flags
	bool _closed;
	bool _out;
	bool _opening;
	bool _open;

	// animations
	QRect _animClosed;
	QRect _animOpen[3];
	QRect _animOut[3];

	// type of Power Up
	char _type;

	int _life = 4;

public:

	TurretPowerUp(QPointF pos, char type);

	// implemented abstract methods
	virtual void animate() override;
	virtual std::string name() override { return "TurretPowerUp[" + std::to_string(_id) + "]"; }

	// reimplemented abstract methods
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual void advance() override;

	// getters
	char typePowerUp() const { return _type; }
	bool Out() const { return _out; }
};