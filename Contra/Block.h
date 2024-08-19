#pragma once

#include "StaticObject.h"

namespace Contra
{
	class Block;
}

class Contra::Block : public StaticObject
{
private:

	// state flags
	bool _passable;

public:

	Block(QPointF pos, double width, double height, bool pass = true) :
		StaticObject(pos, width, height) {
		_passable = pass;
	}

	// implemented abstract methods
	virtual bool hit(Object* what, Direction fromDir) override {return true;}
	virtual std::string name() override { return "Block[" + std::to_string(_id) + "]"; }

	// Getter
	bool passable() const { return _passable; }
};