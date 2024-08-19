#pragma once

#include "Vec2D.h"

namespace Contra
{
	extern bool RayVsRect(
		const Vec2Df& ray_origin,
		const Vec2Df& ray_dir,
		const RectF& target,
		Vec2Df& contact_point,
		Vec2Df& contact_normal,
		double& t_hit_near);

	extern bool DynamicRectVsRect(
		const RectF& source,
		const Vec2Df& source_vel,
		const RectF& target,
		Vec2Df& contact_point,
		Vec2Df& contact_normal,
		double& contact_time);
}
