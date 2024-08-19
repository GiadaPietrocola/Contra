#include "DynamicObject.h"
#include "StaticObject.h"
#include "Game.h"
#include "GameConfig.h"
#include "CollisionDetection.h"
#include "Block.h"
#include "Bridge.h"
#include "Water.h"

using namespace Contra;

DynamicObject::DynamicObject(QPointF pos, double width, double height) :
	Object(pos, width, height)
{
	// dynamic objects are compenetrable vs. each other by default
	// (e.g. collectibles vs. enemies)
	_compenetrable = true;

	// default movement (stand)
	_x_dir = _prev_x_dir = Direction::NONE;
	_vel = { 0, 0 };

	_mirror_x_dir = Direction::NONE;

	defaultPhysics();
}

void DynamicObject::defaultPhysics()
{
	_y_gravity = 0.1;
	_y_acc_jmp = 3.7;
	_x_acc_jmp = 1;

	_y_vel_max = 3.7;
	_y_vel_min = 0.01; // 0.01

	_x_vel_max = 0.8;
	_x_vel_min = 0.01;
	
	_x_acc = _x_vel_max;
	_x_dec_rel = _x_vel_max;
	_x_dec_skd = _x_vel_max;
	

}

void DynamicObject::velClipX(double vx)
{
	_vel.x = std::max(_vel.x, -vx);
	_vel.x = std::min(_vel.x, vx);
}

void DynamicObject::velClipY(double vy)
{
	_vel.y = std::max(_vel.y, -vy);
	_vel.y = std::min(_vel.y, vy);
}

void DynamicObject::velAdd(Vec2Df amount)
{
	_vel += amount;

	// max velocity clipping
	velClipX(_x_vel_max);
	velClipY(_y_vel_max);

	// min velocity clipping
	if (_x_dir == Direction::NONE && std::abs(_vel.x) < _x_vel_min)
		_vel.x = 0;
	if (std::abs(_vel.y) < _y_vel_min)
		_vel.y = 0;
}

void DynamicObject::move(Direction dir)
{
	if (dir != _x_dir)
		_prev_x_dir = _x_dir;

	_x_dir = dir;
}

void DynamicObject::jump()
{
	if (!midair())
		velAdd(Vec2Df(0, -_y_acc_jmp));
}

bool DynamicObject::grounded() const
{
	return _vel.y == 0 && _prev_vel.y > 0;
}

bool DynamicObject::falling() const
{
	return _vel.y > 0; //&& _prev_vel.y <= 0;
}

bool DynamicObject::midair() const
{
	return _vel.y != 0 || (_vel.y == 0 && _prev_vel.y < 0);
}


void DynamicObject::advance()
{
	// velocity backup (useful to determine object state)
	_prev_vel = _vel;

	// apply gravity acceleration
	velAdd(Vec2Df(0, _y_gravity));


	// apply horizontal accelerations and decelerations

	// detect and resolve collisions if needed
	if (_collidable)
		resolveCollisions();



	// move
	setX(x() + _vel.x);
	setY(y() + _vel.y);
}

bool DynamicObject::collidableWith(Object* obj, Direction dir)
{
	if (obj->to<Block*>() && dir != Direction::DOWN){
		return false;
	}
	else {
		return true;
	}
}


void DynamicObject::resolveCollisions()
{

	// simulate next frame pos to get objects within united bounding rect
	QPointF curPos = pos();
	QRectF curRect = qsceneCollider();
	setX(x() + _vel.x);
	setY(y() + _vel.y);
	QList<Object*> likely_collisions;
	QList<QGraphicsItem*> items_in_rect = Game::instance()->world()->items(qsceneCollider().united(curRect));
	for (auto item : items_in_rect)
	{
		Object* obj = dynamic_cast<Object*>(item);
		if (obj && obj->collidable() && obj != this)
			likely_collisions.push_back(obj);
	}
	setPos(curPos);	// restore current pos

	// sort collisions in ascending order of contact time
	Vec2Df cp, cn;
	double ct = 0, min_t = INFINITY;
	std::vector<std::pair<Object*, double>> sortedByContactTime;
	for (auto& obj : likely_collisions) {
		//std::cout << obj->name()<<"\n";

		if (DynamicRectVsRect(sceneCollider(), vel(), obj->sceneCollider(), cp, cn, ct))
			sortedByContactTime.push_back({ obj, ct });
		std::sort(sortedByContactTime.begin(), sortedByContactTime.end(),
			[this](const std::pair<Object*, double>& a, const std::pair<Object*, double>& b)
			{
				// if contact time is the same, give priority to nearest object
				return a.second != b.second ? a.second < b.second : dist(a.first) < dist(b.first);
			});
		}

	// solve the collisions in correct order 
	for (auto obj : sortedByContactTime)
		if (DynamicRectVsRect(sceneCollider(), vel(), obj.first->sceneCollider(), cp, cn, ct))
		{
			
			if (!obj.first->compenetrable() && collidableWith(obj.first, inverse(normal2dir(cn)))){
				velAdd(cn * Vec2Df(std::abs(_vel.x), std::abs(_vel.y)) * (1 - ct));
				//std::cout << "collisione";
			}


			obj.first->hit(this, normal2dir(cn));
			hit(obj.first, inverse(normal2dir(cn)));
			
			
		}
	
}

void DynamicObject::paint(QPainter* painter)
{
	// x-mirroring
	if (_mirror_x_dir != Direction::NONE &&
		(_x_dir == _mirror_x_dir || (_x_dir == Direction::NONE && _prev_x_dir == _mirror_x_dir)))
	{
		painter->translate(_boundingRect.width(), 0);	// move x origin to right side
		painter->scale(-1, 1);							// mirror x-axis
	}
	

	Object::paint(painter);
}