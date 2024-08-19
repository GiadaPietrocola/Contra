#pragma once

#include <QGraphicsItem>
#include "Vec2D.h"
#include "Direction.h"
#include "Scheduler.h"

namespace Contra
{
	class Object;
}

class Contra::Object : public QGraphicsItem
{
protected:

	QRectF _boundingRect;
	QRectF _collider;
	bool _collidable;
	bool _compenetrable;

	bool _dead;

	QPixmap* _sprite;
	QRect* _animRect;

	std::map<std::string, Scheduler> _schedulers;

	int _id;					// for debugging
	bool _colliderVisible;		// for debugging

public:

	Object(QPointF pos, double width, double height);

	// getters
	int id() const { return _id; }
	QRectF boundingRect() const override { return _boundingRect; }
	QRectF collider() const { return _collider; }
	virtual bool collidable() const { return _collidable; }
	bool compenetrable() const { return _compenetrable; }
	bool isDead() const { return _dead; }

	// advanced getters for collision detection
	QRectF qsceneCollider() const;
	RectF sceneCollider() const;
	double dist(Object* obj) const;

	// compute next location
	virtual void advance() = 0;

	// compute next animation
	virtual void animate() = 0;

	// draw
	virtual void paint(QPainter* painter);
	// implemented abstract method from QGraphicsItem
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	// hit by another object, return true if hit is resolved
	virtual bool hit(Object* what, Direction fromDir) = 0;

	// action scheduling
	virtual void schedule(const std::string& id, int delay, std::function<void()> action, bool overwrite = true);
	virtual void updateSchedulers();

	// name for debug purposes
	virtual std::string name() = 0;

	// conversion
	template <class T>
	T to() { return dynamic_cast<T>(this); }

	// show / hide collider
	void toggleCollider();

};