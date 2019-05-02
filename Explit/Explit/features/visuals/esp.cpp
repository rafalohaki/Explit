#include "esp.hpp"
c_esp g_esp;

void c_esp::start()
{
	if (g_config.settings.visuals.esp.esp)
	{
		for (int i = 1; i < g_interfaces.p_engine->GetMaxClients(); i++) {
			const auto entity = reinterpret_cast<C_BaseEntity*>(g_interfaces.p_entitylist->GetClientEntity((i)));
			if (!entity)
				continue;
			if (entity->IsDormant())
				continue;
			if (entity == g_interfaces.g_localplayer)
				continue;

			const auto box = get_boundbox(entity);

			if (g_config.settings.visuals.esp.local)draw_players(entity, box);
		}
	}

}

void c_esp::draw_players(C_BaseEntity* pplayer, RECT box)
{
	int text_position = box.top - 1;
	int bar_position = box.left - 4;
	if (g_config.settings.visuals.esp.box)
	{
		switch (g_config.settings.visuals.esp.box_type)
		{
		case 0:
		{
			if (g_config.settings.visuals.esp.outline_box)
			{
				g_draw.rect(box.left - 1, box.top - 1, box.right - box.left + 2, box.bottom - box.top + 2, Color(1, 1, 1));
				g_draw.rect(box.left + 1, box.top + 1, box.right - box.left - 2, box.bottom - box.top - 2, Color(1, 1, 1));
			}
			g_draw.rect(box.left, box.top, box.right - box.left, box.bottom - box.top, Color(255, 0, 0));
			break;
		}
		case 1:
		{
			if(g_config.settings.visuals.esp.outline_box)
			{ 
				g_draw.fill_rect(box.left - 1, box.top - 1, (box.right - box.left) / 3 + 2, 3, Color(1, 1, 1));
				g_draw.fill_rect(box.right - 2 - (box.right - box.left) / 3, box.top - 1, (box.right - box.left) / 3 + 3, 3, Color(1, 1, 1));

				g_draw.fill_rect(box.left - 1, box.bottom - 2, (box.right - box.left) / 3 + 2, 3, Color(1, 1, 1));
				g_draw.fill_rect(box.right - 2 - (box.right - box.left) / 3, box.bottom - 2, (box.right - box.left) / 3 + 3, 3, Color(1, 1, 1));

				g_draw.fill_rect(box.left - 1, box.top - 1, 3, (box.bottom - box.top) / 3 + 2, Color(1, 1, 1));
				g_draw.fill_rect(box.right - 2, box.top - 1, 3, (box.bottom - box.top) / 3 + 2, Color(1, 1, 1));

				g_draw.fill_rect(box.left - 1, box.bottom - (box.bottom - box.top) / 3 - 1 , 3, (box.bottom - box.top) / 3 + 2, Color(1, 1, 1));
				g_draw.fill_rect(box.right - 2, box.bottom -  (box.bottom - box.top) / 3 - 1, 3, (box.bottom - box.top) / 3 + 2, Color(1, 1, 1));
			}
			g_draw.line(box.left, box.top, box.left + (box.right - box.left) / 3, box.top, Color(255, 0, 0));
			g_draw.line(box.right - (box.right - box.left) / 3 - 1, box.top, box.right - 1, box.top, Color(255, 0, 0));

			g_draw.line(box.left, box.top, box.left, box.top + (box.bottom - box.top) / 3, Color(255, 0, 0));
			g_draw.line(box.right - 1, box.top, box.right - 1	, box.top + (box.bottom - box.top) / 3, Color(255, 0, 0));
				
			g_draw.line(box.left, box.bottom - 1, box.left + (box.right - box.left) / 3, box.bottom - 1, Color(255, 0, 0));
			g_draw.line(box.right - (box.right - box.left) / 3 - 1, box.bottom - 1, box.right - 1, box.bottom - 1, Color(255, 0, 0));

			g_draw.line(box.left, box.bottom - (box.bottom - box.top) / 3, box.left, box.bottom, Color(255, 0, 0));
			g_draw.line(box.right - 1, box.bottom - (box.bottom - box.top) / 3, box.right - 1, box.bottom, Color(255, 0, 0));
			break;
		}
		default:
			break;
		}
	}
	if (g_config.settings.visuals.esp.fill_box)
	{
		g_draw.fill_rect(box.left + 1, box.top + 1, box.right - box.left - 2, box.bottom - box.top - 2, Color(1, 1, 1,130));
	}
	if (g_config.settings.visuals.esp.name)
	{
		g_draw.string(box.left + (box.right - box.left) / 2, box.top - 13, Color(255, 255, 255), g_draw.esp, true, pplayer->get_name());
	}
	if (g_config.settings.visuals.esp.health)
	{
		switch (g_config.settings.visuals.esp.health)
		{
		case 1:
		{
			const auto hp = pplayer->m_iHealth();
			auto green = int(hp * 2.55f);
			auto red = 255 - green;
			const auto height = ((box.bottom - box.top) * hp) / 100;

			if (g_config.settings.visuals.esp.outline_box)
			{
				g_draw.fill_rect(bar_position - 1, box.top - 1, 3, box.bottom - box.top + 2, Color(1, 1, 1));
			}

			g_draw.fill_rect(bar_position, box.bottom - height, 1, height , Color(red, green, 0));

			bar_position -= 4;
			break;
		}
		case 2:
		{
			g_draw.string(box.right + 3, text_position, Color(255, 255, 255), g_draw.esp, false, g_utils.stringer(pplayer->m_iHealth(), "HP"));
			text_position += 12;
			break;
		}
		case 3:
		{
			const auto hp = pplayer->m_iHealth();
			const auto green = static_cast<int>(hp * 2.55f);
			const auto red = 255 - green;
			const auto height = ((box.bottom - box.top) * hp) / 100;

			if (g_config.settings.visuals.esp.outline_box)
			{
				g_draw.fill_rect(bar_position - 1, box.top - 1, 3, box.bottom - box.top + 2, Color(1, 1, 1));
			}

			g_draw.fill_rect(bar_position, box.bottom - height, 1, height , Color(red, green, 0));
			g_draw.string(box.right + 3, text_position, Color(255, 255, 255), g_draw.esp, false, g_utils.stringer(hp, "HP"));

			text_position += 12;
			bar_position -= 4;
			break;
		}
		default:
			break;
		}
	}
	if (g_config.settings.visuals.esp.armor)
	{
		switch (g_config.settings.visuals.esp.armor)
		{
		case 1:
		{
			const auto armor = pplayer->m_ArmorValue();
			const auto height = ((box.bottom - box.top) * armor) / 100;

			if (g_config.settings.visuals.esp.outline_box)
			{
				g_draw.fill_rect(bar_position - 1, box.top - 1, 3, box.bottom - box.top + 2, Color(1, 1, 1));
			}

			g_draw.fill_rect(bar_position, box.bottom - height, 1, height, Color(55, 130, 213));

			bar_position -= 4;
			break;
		}
		case 2:
		{
			if (const auto armor = pplayer->m_ArmorValue(); armor > 0)
			{
				const auto armor_str = pplayer->m_bHasHelmet() ? "K+H" : "K";
				g_draw.string(box.right + 3, text_position, Color(55, 130, 213), g_draw.esp, false, g_utils.stringer(armor, armor_str));
				text_position += 12;
			}

			break;
		}
		case 3:
		{
			const auto armor = pplayer->m_ArmorValue();
			const auto height = ((box.bottom - box.top) * armor) / 100;

			if (g_config.settings.visuals.esp.outline_box)
			{
				g_draw.fill_rect(bar_position - 1, box.top - 1, 3, box.bottom - box.top + 2, Color(1, 1, 1));
			}

			g_draw.fill_rect(bar_position, box.bottom - height, 1, height, Color(55, 130, 213));

			bar_position -= 4;

			if (armor > 0)
			{
				const auto armor_str = pplayer->m_bHasHelmet() ? "K+H" : "K";
				g_draw.string(box.right + 3, text_position, Color(55, 130, 213), g_draw.esp, false, g_utils.stringer(armor, armor_str));
				text_position += 12;
			}

			break;
		}
		}
	}
	if (g_config.settings.visuals.esp.money)
	{
		g_draw.string(box.right + 3, text_position - 1, Color(0, 255, 0), g_draw.esp, false, g_utils.stringer("$", pplayer->m_iAccount()));
		text_position += 12;
	}
	if (g_config.settings.visuals.esp.distance)
	{
		g_draw.string(box.right + 3, text_position - 1, Color(255, 255, 255), g_draw.esp, false, g_utils.stringer(pplayer->get_distance(),"m"));
		text_position += 12;
	}


}

RECT c_esp::get_boundbox(C_BaseEntity* pent)
{
	RECT box{};
	if (!pent)
		return box;

	const matrix3x4_t& trans = pent->m_rgflCoordinateFrame();

	const auto collision = pent->GetCollideable();
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