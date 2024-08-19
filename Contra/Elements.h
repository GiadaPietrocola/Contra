#pragma once

#include "Object.h"

namespace Contra
{
	class FlashingElements;
	class Medals;
	class Text;
	class Title;
}

class Contra::FlashingElements : public Object
{
private:

	// animations
	QRect _animFlashing[2];

public:

	FlashingElements();

	// implemented abstract methods
	virtual void advance() override {}
	virtual void animate() override;
	virtual bool hit(Object* what, Direction fromDir) override { return true; }
	virtual std::string name() override { return "FlashingElements"; }
};

class Contra::Medals : public Object {

private:

	// animations
	QRect _animMedals[4];

public:

	Medals();

	// implemented abstract methods
	virtual void advance() override;
	virtual void animate() override;
	virtual bool hit(Object* what, Direction fromDir) override { return true; }
	virtual std::string name() override { return "Medals"; }
};

class Contra::Text : public Object
{
private:

	QPixmap _pixText;
	QRect _animText;

public:

	Text(std::string text);

	// implemented abstract methods
	virtual void advance() override {}
	virtual void animate() override {};
	virtual bool hit(Object* what, Direction fromDir) override { return true; }
	virtual std::string name() override { return "Text"; }
};

class Contra::Title : public Object
{
private:

	// state flags
	bool _moving;

	// animations
	QRect _animTitle;
	

public:

	Title();

	// implemented abstract methods
	virtual void advance() override;
	virtual void animate() override {}
	virtual bool hit(Object* what, Direction fromDir) override { return true; }
	virtual std::string name() override { return "Title"; }
};