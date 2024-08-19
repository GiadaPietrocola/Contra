#pragma once

#include "Object.h"

namespace Contra
{
	class Explosion;
}

class Contra::Explosion : public Object
{
private:

	// state flags
	bool _exploded;

	// animations
	QRect _animExplosionBridge[7];
	QRect _animExplosion[5];

	int _type;
	int _animCounter = 0;

public:

	Explosion(int type, QPointF pos);

	// implemented abstract methods
	virtual void advance() override;
	virtual void animate() override;
	virtual bool hit(Object* what, Direction fromDir) override { return true; }
	virtual std::string name() override { return "Explosion"; }
};