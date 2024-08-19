#include "CollisionDetection.h"
#include "Direction.h"

using namespace Contra;

bool Contra::RayVsRect(
	const Vec2Df& ray_origin,
	const Vec2Df& ray_dir,
	const RectF& target,
	Vec2Df& contact_point,
	Vec2Df& contact_normal,
	double& t_hit_near)
{
	contact_normal = { 0,0 };
	contact_point = { 0,0 };

	// cache division
	// ray_dir.x (velocity.x) = 0 will yield +infinity, which is ok
	// <=> no intersection along x. Same applies to y
	Vec2Df invdir = 1.0 / ray_dir;

	// calculate intersections with rectangle bounding axes
	Vec2Df t_near = (target.pos - ray_origin) * invdir;
	Vec2Df t_far = (target.pos + target.size - ray_origin) * invdir;

	// above lines may yield 0 * infinity = NaN, which is NOT ok
	// <=> one of the target sides touch ray dir
	// <=> collision is NOT happening
	if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
	if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

	// swap distances if necessary
	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

	// early collision rejection		
	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

	// contact time will be the second t_near point along ray
	t_hit_near = std::max(t_near.x, t_near.y);

	// exit contact time is the first t_far point along ray
	double t_hit_far = std::min(t_far.x, t_far.y);

	// reject if ray direction is pointing away from object
	if (t_hit_far < 0)
		return false;

	// contact point of collision from parametric line equation
	contact_point = ray_origin + t_hit_near * ray_dir;

	// contact normal
	if (t_near.x > t_near.y)
		if (invdir.x < 0)
			contact_normal = { 1,  0 };
		else
			contact_normal = { -1,  0 };
	else
		if (invdir.y < 0)
			contact_normal = { 0,  1 };
		else
			contact_normal = { 0, -1 };

	// Note if t_near == t_far, collision is in a diagonal
	// we consider this case in the "else" branch which is
	// equivalent to assume that diagonal collisions
	// are resolved along the vertical axis
	return true;
}

bool Contra::DynamicRectVsRect(
	const RectF& source,
	const Vec2Df& source_vel,
	const RectF& target,
	Vec2Df& contact_point,
	Vec2Df& contact_normal,
	double& contact_time)
{
	// expand target rectangle by source dimensions
	RectF expanded_target;
	expanded_target.pos = target.pos - source.size / 2;
	expanded_target.size = target.size + source.size;

	// perform ray vs rect intersection
	if (RayVsRect(source.pos + source.size / 2, source_vel, expanded_target, contact_point, contact_normal, contact_time)) {
		return (contact_time >= 0 - 0.0001 && contact_time <= 1.0);
		
	}
	else return false;
		

}
