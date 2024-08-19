#pragma once

#include "Enemy.h"

namespace Contra
{
	class Core;
}

class Contra::Core : public Enemy
{
private:

	// animations
	QRect _animGlowing[3];

	int _life = 12;

public:

	Core(QPointF pos);

	// implemented abstract methods
	virtual void animate() override;
	virtual std::string name() override { return "Core[" + std::to_string(_id) + "]"; }

	// reimplemented abstract methods
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual void advance() override;
};