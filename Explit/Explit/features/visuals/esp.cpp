#include "esp.hpp"
c_esp g_esp;

void c_esp::start()
{
	if (g_sdk.esp) 
	{
		for (int i = 1; i < g_interfaces.p_engine->GetMaxClients(); i++) {
			const auto entity = static_cast<C_BaseEntity*>(g_interfaces.p_entitylist->GetClientEntity((i)));
			if (!entity)
				continue;
			if (entity->IsDormant())
				continue;
			if (entity->GetClientClass()->ClassID != ClassID::CCSPlayer)
				continue;
			if (entity == g_interfaces.g_localplayer)
				continue;
			auto box = get_boundbox(entity);
			draw_players(entity, box);
		}
	}
}

void c_esp::draw_players(C_BaseEntity* pplayer, RECT box)
{
	g_draw.rect(box.left, box.top, box.right - box.left, box.bottom - box.top, Color(255, 0, 0));
}

RECT c_esp::get_boundbox(C_BaseEntity* pent)
{
	RECT box{};
	if (!pent)
		return box;

	const matrix3x4_t& trans = pent->m_rgflCoordinateFrame();

	const auto collision = pent->get_collideable();
	if (!collision)
		return box;

	const auto min = collision->OBBMins();
	const auto max = collision->OBBMaxs();

	Vector points[] = { Vector(min.x, min.y, min.z),
					Vector(min.x, max.y, min.z),
					Vector(max.x, max.y, min.z),
					Vector(max.x, min.y, min.z),
					Vector(max.x, max.y, max.z),
					Vector(min.x, max.y, max.z),
					Vector(min.x, min.y, max.z),
					Vector(max.x, min.y, max.z) };

	Vector points_transformed[8];
	for (int i = 0; i < 8; i++)
	{
		g_math.vector_transform(points[i], trans, points_transformed[i]);
	}

	Vector screen_points[8];
	for (int i = 0; i < 8; i++) {
		if (!g_math.world_to_screen(points_transformed[i], screen_points[i]))
			return box;
	}

	auto left = screen_points[0].x;
	auto top = screen_points[0].y;
	auto right = screen_points[0].x;
	auto bottom = screen_points[0].y;

	for (int i = 1; i < 8; i++) {
		if (left > screen_points[i].x)
			left = screen_points[i].x;
		if (top < screen_points[i].y)
			top = screen_points[i].y;
		if (right < screen_points[i].x)
			right = screen_points[i].x;
		if (bottom > screen_points[i].y)
			bottom = screen_points[i].y;
	}

	box = RECT{ (long)(left),  static_cast<LONG>(bottom), static_cast<LONG>(right), static_cast<LONG>(top) };

	return box;
}