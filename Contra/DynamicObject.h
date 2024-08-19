#pragma once

#include "Object.h"

namespace Contra
{
	class DynamicObject;
}

class Contra::DynamicObject : public Object
{
protected:

	// physics parameters (expressed in pixels/frame unit)
	double _y_gravity;		// vertical acceleration due to gravity
	double _x_acc;			// horizontal acceleration due to movement
	double _x_dec_rel;		// horizontal deceleration due to movement release
	double _x_dec_skd;		// horizontal deceleration due to skidding (movement change)
	double _x_vel_max;		// maximum horizontal velocity
	double _x_vel_min;		// minimum horizontal velocity
	double _y_vel_max;		// maximum vertical velocity
	double _y_vel_min;		// minimum vertical velocity
	double _y_acc_jmp;		// initial vertical velocity when jumping
	double _x_acc_jmp;		// initial horizontal velocity when jumping

	// attributes
	Direction _x_dir;		// current horizontal movement direction
	Direction _prev_x_dir;	// previous horizontal movement direction
	Direction _mirror_x_dir;// direction that needs animation mirroring
	Vec2Df _vel;			// current velocity
	Vec2Df _prev_vel;		// velocity in the previous frame

	// collision detection/resolution
	virtual void resolveCollisions();
	virtual bool collidableWith(Object* obj, Direction dir);

public:

	DynamicObject(QPointF pos, double width, double height);

	// getters / setters
	Vec2Df vel() const { return _vel; }
	void velAdd(Vec2Df amount);
	void velClipX(double vx);
	void velClipY(double vx);

	// state queries
	bool skidding() const;
	bool grounded() const;
	bool falling() const;
	bool midair() const;

	// actions
	virtual void move(Direction dir);
	virtual void jump();

	// game physics
	virtual void advance() override;
	virtual void defaultPhysics();

	// nonimplemented abstract methods
	virtual void animate() override = 0;
	virtual bool hit(Object* what, Direction fromDir) override = 0;
	virtual std::string name() override = 0;

	// reimplemented methods
	virtual void paint(QPainter* painter) override;
};