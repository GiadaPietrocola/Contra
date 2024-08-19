#include <QPainter>
#include <QBrush>
#include <QPen>
#include "Object.h"
#include "Game.h"
#include "GameConfig.h"

using namespace Contra;

static int created = 0;

Object::Object(QPointF pos, double width, double height)
{
	_id = created++;
	_collidable = true;
	_compenetrable = false;
	_colliderVisible = false;
	_boundingRect = QRectF(0, 0, width, height);
	_collider = _boundingRect;

	_dead = false;

	_sprite = nullptr;
	_animRect = nullptr;

	Game::instance()->world()->addItem(this);

	setPos(pos);
}

QRectF Object::qsceneCollider() const
{
	return mapRectToScene(_collider);
}

RectF Object::sceneCollider() const
{
	QRectF coll = qsceneCollider();
	return RectF{ {coll.x(), coll.y()}, {coll.width(), coll.height()} };
}

double Object::dist(Object* obj) const
{
	QPointF p1 = qsceneCollider().center();
	QPointF p2 = obj->qsceneCollider().center();
	return std::sqrt((p2.x() - p1.x()) * (p2.x() - p1.x()) + (p2.y() - p1.y()) * (p2.y() - p1.y()));
}

void Object::toggleCollider()
{
	if (_collidable)
		_colliderVisible = !_colliderVisible;
}

void Object::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	paint(painter);

	if (_colliderVisible)
	{
		painter->setPen(QPen(QBrush(Qt::red), 0.5));
		painter->setBrush(Qt::NoBrush);
		painter->drawRect(_collider);
	}

}

void Object::paint(QPainter* painter)
{
	if (_animRect && _sprite)
		painter->drawPixmap(_boundingRect, *_sprite, *_animRect);
}

void Object::schedule(const std::string& id, int delay, std::function<void()> action, bool overwrite)
{
	if (overwrite || _schedulers.find(id) == _schedulers.end())
		_schedulers[id] = Scheduler(delay, action);
}

void Object::updateSchedulers()
{
	auto iter = _schedulers.begin();
	for (; iter != _schedulers.end(); )
	{
		if (iter->second.on())
		{
			iter->second++;
			++iter;
		}
		else
			iter = _schedulers.erase(iter);
	}
}