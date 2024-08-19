#pragma once

#include "StaticObject.h"

namespace Contra
{
	class Bridge;
}

class Contra::Bridge : public StaticObject
{
private:

	// state flags
	bool _exploding;

	// animatios
	QRect _animBridge[3];
	QRect _animExplosion[3][3];

	int _explodingTime;
public:

	Bridge(QPointF pos, double width, double height);

	// implemented abstract methods
	virtual void advance() override;
	virtual void animate() override;
	virtual bool hit(Object* what, Direction fromDir) override { return true; }
	virtual std::string name() override { return "Bridge[" + std::to_string(_id) + "]"; }

	// action
	void explode();
};