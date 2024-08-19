#pragma once

#include "StaticObject.h"

namespace Contra
{
	class Water;
}

class Contra::Water : public StaticObject
{
public:

	Water(QPointF pos, double width, double height) :
		StaticObject(pos, width, height) {}

	// implemented abstract methods
	virtual bool hit(Object* what, Direction fromDir) override { return true; }
	virtual std::string name() override { return "Water[" + std::to_string(_id) + "]"; }

};