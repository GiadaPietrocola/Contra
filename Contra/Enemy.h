#pragma once

#include "DynamicObject.h"

namespace Contra
{
	class Enemy;
}

class Contra::Enemy : public DynamicObject
{
public:

	Enemy(QPointF pos, double width, double height);

	// implemented abstract methods
	virtual bool hit(Object* what, Direction fromDir) override;

	// nonimplemented abstract methods
	virtual void animate() override = 0;
	virtual std::string name() override = 0;
};