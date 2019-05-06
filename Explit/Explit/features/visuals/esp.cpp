#include "esp.hpp"
c_esp g_esp;

void c_esp::start()
{
	if (g_config.settings.visuals.esp.esp)
	{
		for (int i = 1; i <= g_interfaces.p_entity_list->get_highest_entity_index(); i++) {
			const auto p_entity = reinterpret_cast<c_base_entity*>(g_interfaces.p_entity_list->get_client_entity((i)));
			if (!p_entity)
				continue;
			if (p_entity->is_dormant())
				continue;
			if (p_entity == g_interfaces.g_local_player && !g_config.settings.visuals.esp.local)
				continue;

			const auto box = get_boundbox(p_entity);

			if (IsRectEmpty(&box))
				continue;

			if (g_config.settings.visuals.esp.weapons && p_entity->is_weapon()) 
				draw_weapons(p_entity, box);
			if(g_config.settings.visuals.esp.chickens && p_entity->is_chicken())
				draw_chickens(p_entity, box);
			if(g_config.settings.visuals.esp.enemies && p_entity->m_iteamnum() != g_interfaces.g_local_player->m_iteamnum() && p_entity->is_valid())
				draw_players(p_entity, box);
			if (g_config.settings.visuals.esp.team && p_entity->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() && p_entity->is_valid())
				draw_players(p_entity, box);

		}
	}

}

void c_esp::draw_players(c_base_entity* p_player, const RECT box)
{
	int text_position = box.top - 1;
	int bar_position = box.left - 4;
	int weapon_position = box.bottom + 2;

	if (g_config.settings.visuals.esp.box)
	{
		switch (g_config.settings.visuals.esp.box_type)
		{
		case 0:
		{
			if (g_config.settings.visuals.esp.outline_box)
			{
				g_draw.rect(box.left - 1, box.top - 1, box.right - box.left + 2, box.bottom - box.top + 2, color(1, 1, 1));
				g_draw.rect(box.left + 1, box.top + 1, box.right - box.left - 2, box.bottom - box.top - 2, color(1, 1, 1));
			}
			g_draw.rect(box.left, box.top, box.right - box.left, box.bottom - box.top, p_player->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() ? color(g_config.settings.visuals.esp.colors.team_visible[0], g_config.settings.visuals.esp.colors.team_visible[1], g_config.settings.visuals.esp.colors.team_visible[2], 255.f) : color(g_config.settings.visuals.esp.colors.enemy_visible[0], g_config.settings.visuals.esp.colors.enemy_visible[1], g_config.settings.visuals.esp.colors.enemy_visible[2],255.f));
			break;
		}
		case 1:
		{
			if(g_config.settings.visuals.esp.outline_box)
			{ 
				g_draw.fill_rect(box.left - 1, box.top - 1, (box.right - box.left) / 3 + 2, 3, color(1, 1, 1));
				g_draw.fill_rect(box.right - 2 - (box.right - box.left) / 3, box.top - 1, (box.right - box.left) / 3 + 3, 3, color(1, 1, 1));

				g_draw.fill_rect(box.left - 1, box.bottom - 2, (box.right - box.left) / 3 + 2, 3, color(1, 1, 1));
				g_draw.fill_rect(box.right - 2 - (box.right - box.left) / 3, box.bottom - 2, (box.right - box.left) / 3 + 3, 3, color(1, 1, 1));

				g_draw.fill_rect(box.left - 1, box.top - 1, 3, (box.bottom - box.top) / 3 + 2, color(1, 1, 1));
				g_draw.fill_rect(box.right - 2, box.top - 1, 3, (box.bottom - box.top) / 3 + 2, color(1, 1, 1));

				g_draw.fill_rect(box.left - 1, box.bottom - (box.bottom - box.top) / 3 - 1 , 3, (box.bottom - box.top) / 3 + 2, color(1, 1, 1));
				g_draw.fill_rect(box.right - 2, box.bottom -  (box.bottom - box.top) / 3 - 1, 3, (box.bottom - box.top) / 3 + 2, color(1, 1, 1));
			}
			g_draw.line(box.left, box.top, box.left + (box.right - box.left) / 3, box.top, p_player->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() ? color(g_config.settings.visuals.esp.colors.team_visible[0], g_config.settings.visuals.esp.colors.team_visible[1], g_config.settings.visuals.esp.colors.team_visible[2]) : color(g_config.settings.visuals.esp.colors.enemy_visible[0], g_config.settings.visuals.esp.colors.enemy_visible[1], g_config.settings.visuals.esp.colors.enemy_visible[2]));
			g_draw.line(box.right - (box.right - box.left) / 3 - 1, box.top, box.right - 1, box.top, p_player->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() ? color(g_config.settings.visuals.esp.colors.team_visible[0], g_config.settings.visuals.esp.colors.team_visible[1], g_config.settings.visuals.esp.colors.team_visible[2]) : color(g_config.settings.visuals.esp.colors.enemy_visible[0], g_config.settings.visuals.esp.colors.enemy_visible[1], g_config.settings.visuals.esp.colors.enemy_visible[2]));

			g_draw.line(box.left, box.top, box.left, box.top + (box.bottom - box.top) / 3, p_player->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() ? color(g_config.settings.visuals.esp.colors.team_visible[0], g_config.settings.visuals.esp.colors.team_visible[1], g_config.settings.visuals.esp.colors.team_visible[2]) : color(g_config.settings.visuals.esp.colors.enemy_visible[0], g_config.settings.visuals.esp.colors.enemy_visible[1], g_config.settings.visuals.esp.colors.enemy_visible[2]));
			g_draw.line(box.right - 1, box.top, box.right - 1	, box.top + (box.bottom - box.top) / 3, p_player->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() ? color(g_config.settings.visuals.esp.colors.team_visible[0], g_config.settings.visuals.esp.colors.team_visible[1], g_config.settings.visuals.esp.colors.team_visible[2]) : color(g_config.settings.visuals.esp.colors.enemy_visible[0], g_config.settings.visuals.esp.colors.enemy_visible[1], g_config.settings.visuals.esp.colors.enemy_visible[2]));
				
			g_draw.line(box.left, box.bottom - 1, box.left + (box.right - box.left) / 3, box.bottom - 1, p_player->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() ? color(g_config.settings.visuals.esp.colors.team_visible[0], g_config.settings.visuals.esp.colors.team_visible[1], g_config.settings.visuals.esp.colors.team_visible[2]) : color(g_config.settings.visuals.esp.colors.enemy_visible[0], g_config.settings.visuals.esp.colors.enemy_visible[1], g_config.settings.visuals.esp.colors.enemy_visible[2]));
			g_draw.line(box.right - (box.right - box.left) / 3 - 1, box.bottom - 1, box.right - 1, box.bottom - 1, p_player->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() ? color(g_config.settings.visuals.esp.colors.team_visible[0], g_config.settings.visuals.esp.colors.team_visible[1], g_config.settings.visuals.esp.colors.team_visible[2]) : color(g_config.settings.visuals.esp.colors.enemy_visible[0], g_config.settings.visuals.esp.colors.enemy_visible[1], g_config.settings.visuals.esp.colors.enemy_visible[2]));

			g_draw.line(box.left, box.bottom - (box.bottom - box.top) / 3, box.left, box.bottom, p_player->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() ? color(g_config.settings.visuals.esp.colors.team_visible[0], g_config.settings.visuals.esp.colors.team_visible[1], g_config.settings.visuals.esp.colors.team_visible[2]) : color(g_config.settings.visuals.esp.colors.enemy_visible[0], g_config.settings.visuals.esp.colors.enemy_visible[1], g_config.settings.visuals.esp.colors.enemy_visible[2]));
			g_draw.line(box.right - 1, box.bottom - (box.bottom - box.top) / 3, box.right - 1, box.bottom, p_player->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() ? color(g_config.settings.visuals.esp.colors.team_visible[0], g_config.settings.visuals.esp.colors.team_visible[1], g_config.settings.visuals.esp.colors.team_visible[2]) : color(g_config.settings.visuals.esp.colors.enemy_visible[0], g_config.settings.visuals.esp.colors.enemy_visible[1], g_config.settings.visuals.esp.colors.enemy_visible[2]));
			break;
		}
		default:
			break;
		}
	}
	if (g_config.settings.visuals.esp.fill_box)
	{
		g_draw.fill_rect(box.left + 1, box.top + 1, box.right - box.left - 2, box.bottom - box.top - 2, color(1, 1, 1,130));
	}
	if (g_config.settings.visuals.esp.name)
	{
		g_draw.string(box.left + (box.right - box.left) / 2, box.top - 13, color(255, 255, 255), g_draw.esp, true, p_player->get_name());
	}
	if (g_config.settings.visuals.esp.health)
	{
		switch (g_config.settings.visuals.esp.health)
		{
		case 1:
		{
			const auto hp = p_player->m_ihealth();
			const auto green = int(hp * 2.55f);
			const auto red = 255 - green;
			const auto height = ((box.bottom - box.top) * hp) / 100;

			if (g_config.settings.visuals.esp.outline_box)
			{
				g_draw.fill_rect(bar_position - 1, box.top - 1, 3, box.bottom - box.top + 2, color(1, 1, 1));
			}

			g_draw.fill_rect(bar_position, box.bottom - height, 1, height , color(red, green, 0));

			bar_position -= 4;
			break;
		}
		case 2:
		{
			g_draw.string(box.right + 3, text_position, color(255, 255, 255), g_draw.esp, false, g_utils.stringer(p_player->m_ihealth(), "HP"));
			text_position += 12;
			break;
		}
		case 3:
		{
			const auto hp = p_player->m_ihealth();
			const auto green = static_cast<int>(hp * 2.55f);
			const auto red = 255 - green;
			const auto height = ((box.bottom - box.top) * hp) / 100;

			if (g_config.settings.visuals.esp.outline_box)
			{
				g_draw.fill_rect(bar_position - 1, box.top - 1, 3, box.bottom - box.top + 2, color(1, 1, 1));
			}

			g_draw.fill_rect(bar_position, box.bottom - height, 1, height , color(red, green, 0));
			g_draw.string(box.right + 3, text_position, color(255, 255, 255), g_draw.esp, false, g_utils.stringer(hp, "HP"));

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
				const auto armor = p_player->m_armorvalue();
				const auto height = ((box.bottom - box.top) * armor) / 100;

				if (g_config.settings.visuals.esp.outline_box)
				{
					g_draw.fill_rect(bar_position - 1, box.top - 1, 3, box.bottom - box.top + 2, color(1, 1, 1));
				}

				g_draw.fill_rect(bar_position, box.bottom - height, 1, height, color(55, 130, 213));

				bar_position -= 4;
				break;
			}
			case 2:
			{
				if (const auto armor = p_player->m_armorvalue(); armor > 0)
				{
					const auto armor_str = p_player->m_bhashelmet() ? "K+H" : "K";
					g_draw.string(box.right + 3, text_position, color(55, 130, 213), g_draw.esp, false, g_utils.stringer(armor, armor_str));
					text_position += 12;
				}

				break;
			}
			case 3:
			{
				const auto armor = p_player->m_armorvalue();
				const auto height = static_cast<int>(((box.bottom - box.top) * armor) / 100);

				if (g_config.settings.visuals.esp.outline_box)
				{
					g_draw.fill_rect(bar_position - 1, box.top - 1, 3, box.bottom - box.top + 2, color(1, 1, 1));
				}

				g_draw.fill_rect(bar_position, box.bottom - height, 1, height, color(55, 130, 213));

				bar_position -= 4;

				if (armor > 0)
				{
					const auto armor_str = p_player->m_bhashelmet() ? "K+H" : "K";
					g_draw.string(box.right + 3, text_position, color(55, 130, 213), g_draw.esp, false, g_utils.stringer(armor, armor_str));
					text_position += 12;
				}
				break;
			}
		}
	}
	if (g_config.settings.visuals.esp.money)
	{
		g_draw.string(box.right + 3, text_position, color(0, 255, 0), g_draw.esp, false, g_utils.stringer("$", p_player->m_iaccount()));
		text_position += 12;
	}
	if (g_config.settings.visuals.esp.distance)
	{
		if (p_player != g_interfaces.g_local_player)
		{
			g_draw.string(box.right + 3, text_position, color(255, 255, 255), g_draw.esp, false, g_utils.stringer(p_player->get_distance(), "m"));
			text_position += 12;
		}
	}
	if (g_config.settings.visuals.esp.snaplines)
	{
		int width, height;
		g_interfaces.p_engine->get_screen_size(width, height);
		g_draw.line(width / 2, height / 2, box.left + (box.right - box.left) / 2, box.bottom, color(255, 0, 0));
	}
	if (g_config.settings.visuals.esp.weapon)	
	{
		const auto weapon = p_player->get_weapon();
		g_draw.string(box.left + (box.right - box.left) / 2, weapon_position, color(255, 255, 255), g_draw.esp, true, g_utils.stringer("[", weapon->get_weapon_info()->m_weaponname, "]").erase(1, 7));
		weapon_position += 12;
	}
	if (g_config.settings.visuals.esp.ammo)
	{
		const auto weapon = p_player->get_weapon();
		if (const auto max_clip = weapon->get_weapon_info()->m_maxclip; max_clip != -1)
		{
			g_draw.string(box.left + (box.right - box.left) / 2, weapon_position, color(255, 255, 255), g_draw.esp, true, g_utils.stringer("[", weapon->m_iclip1(), "/", max_clip, "]"));
			weapon_position += 12;
		}
	}
}

void c_esp::draw_chickens(c_base_entity* p_player, const RECT box)
{
	if (g_config.settings.visuals.esp.box)
	{
		switch (g_config.settings.visuals.esp.box_type)
		{
		case 0:
		{
			if (g_config.settings.visuals.esp.outline_box)
			{
				g_draw.rect(box.left - 1, box.top - 1, box.right - box.left + 2, box.bottom - box.top + 2, color(1, 1, 1));
				g_draw.rect(box.left + 1, box.top + 1, box.right - box.left - 2, box.bottom - box.top - 2, color(1, 1, 1));
			}
			g_draw.rect(box.left, box.top, box.right - box.left, box.bottom - box.top, color(255, 0, 0));
			break;
		}
		case 1:
		{
			if (g_config.settings.visuals.esp.outline_box)
			{
				g_draw.fill_rect(box.left - 1, box.top - 1, (box.right - box.left) / 3 + 2, 3, color(1, 1, 1));
				g_draw.fill_rect(box.right - 2 - (box.right - box.left) / 3, box.top - 1, (box.right - box.left) / 3 + 3, 3, color(1, 1, 1));

				g_draw.fill_rect(box.left - 1, box.bottom - 2, (box.right - box.left) / 3 + 2, 3, color(1, 1, 1));
				g_draw.fill_rect(box.right - 2 - (box.right - box.left) / 3, box.bottom - 2, (box.right - box.left) / 3 + 3, 3, color(1, 1, 1));

				g_draw.fill_rect(box.left - 1, box.top - 1, 3, (box.bottom - box.top) / 3 + 2, color(1, 1, 1));
				g_draw.fill_rect(box.right - 2, box.top - 1, 3, (box.bottom - box.top) / 3 + 2, color(1, 1, 1));

				g_draw.fill_rect(box.left - 1, box.bottom - (box.bottom - box.top) / 3 - 1, 3, (box.bottom - box.top) / 3 + 2, color(1, 1, 1));
				g_draw.fill_rect(box.right - 2, box.bottom - (box.bottom - box.top) / 3 - 1, 3, (box.bottom - box.top) / 3 + 2, color(1, 1, 1));
			}
			g_draw.line(box.left, box.top, box.left + (box.right - box.left) / 3, box.top, color(255, 0, 0));
			g_draw.line(box.right - (box.right - box.left) / 3 - 1, box.top, box.right - 1, box.top, color(255, 0, 0));

			g_draw.line(box.left, box.top, box.left, box.top + (box.bottom - box.top) / 3, color(255, 0, 0));
			g_draw.line(box.right - 1, box.top, box.right - 1, box.top + (box.bottom - box.top) / 3, color(255, 0, 0));

			g_draw.line(box.left, box.bottom - 1, box.left + (box.right - box.left) / 3, box.bottom - 1, color(255, 0, 0));
			g_draw.line(box.right - (box.right - box.left) / 3 - 1, box.bottom - 1, box.right - 1, box.bottom - 1, color(255, 0, 0));

			g_draw.line(box.left, box.bottom - (box.bottom - box.top) / 3, box.left, box.bottom, color(255, 0, 0));
			g_draw.line(box.right - 1, box.bottom - (box.bottom - box.top) / 3, box.right - 1, box.bottom, color(255, 0, 0));
			break;
		}
		default:
			break;
		}
	}
	if (g_config.settings.visuals.esp.fill_box)
	{
		g_draw.fill_rect(box.left + 1, box.top + 1, box.right - box.left - 2, box.bottom - box.top - 2, color(1, 1, 1, 130));
	}
	if (g_config.settings.visuals.esp.distance)
	{
		g_draw.string(box.right + 3, box.top - 1, color(255, 255, 255), g_draw.esp, false, g_utils.stringer(p_player->get_distance(), "m"));
	}
	if (g_config.settings.visuals.esp.snaplines)
	{
		int width, height;
		g_interfaces.p_engine->get_screen_size(width, height);
		g_draw.line(width / 2, height / 2, box.left + (box.right - box.left) / 2, box.bottom, color(255, 0, 0));
	}
	if (g_config.settings.visuals.esp.name)
	{
		g_draw.string(box.left + (box.right - box.left) / 2, box.top - 13, color(255, 255, 255), g_draw.esp, true, "chicken");
	}
}

void c_esp::draw_weapons(c_base_entity* pentity, const RECT box)
{
	int text_position = box.top - 1;
	int weapon_position = box.bottom + 2;

	if (g_config.settings.visuals.esp.box)
	{
		switch (g_config.settings.visuals.esp.box_type)
		{
		case 0:
		{
			if (g_config.settings.visuals.esp.outline_box)
			{
				g_draw.rect(box.left - 1, box.top - 1, box.right - box.left + 2, box.bottom - box.top + 2, color(1, 1, 1));
				g_draw.rect(box.left + 1, box.top + 1, box.right - box.left - 2, box.bottom - box.top - 2, color(1, 1, 1));
			}
			g_draw.rect(box.left, box.top, box.right - box.left, box.bottom - box.top, color(255, 0, 0));
			break;
		}
		case 1:
		{
			if (g_config.settings.visuals.esp.outline_box)
			{
				g_draw.fill_rect(box.left - 1, box.top - 1, (box.right - box.left) / 3 + 2, 3, color(1, 1, 1));
				g_draw.fill_rect(box.right - 2 - (box.right - box.left) / 3, box.top - 1, (box.right - box.left) / 3 + 3, 3, color(1, 1, 1));

				g_draw.fill_rect(box.left - 1, box.bottom - 2, (box.right - box.left) / 3 + 2, 3, color(1, 1, 1));
				g_draw.fill_rect(box.right - 2 - (box.right - box.left) / 3, box.bottom - 2, (box.right - box.left) / 3 + 3, 3, color(1, 1, 1));

				g_draw.fill_rect(box.left - 1, box.top - 1, 3, (box.bottom - box.top) / 3 + 2, color(1, 1, 1));
				g_draw.fill_rect(box.right - 2, box.top - 1, 3, (box.bottom - box.top) / 3 + 2, color(1, 1, 1));

				g_draw.fill_rect(box.left - 1, box.bottom - (box.bottom - box.top) / 3 - 1, 3, (box.bottom - box.top) / 3 + 2, color(1, 1, 1));
				g_draw.fill_rect(box.right - 2, box.bottom - (box.bottom - box.top) / 3 - 1, 3, (box.bottom - box.top) / 3 + 2, color(1, 1, 1));
			}
			g_draw.line(box.left, box.top, box.left + (box.right - box.left) / 3, box.top, color(255, 0, 0));
			g_draw.line(box.right - (box.right - box.left) / 3 - 1, box.top, box.right - 1, box.top, color(255, 0, 0));

			g_draw.line(box.left, box.top, box.left, box.top + (box.bottom - box.top) / 3, color(255, 0, 0));
			g_draw.line(box.right - 1, box.top, box.right - 1, box.top + (box.bottom - box.top) / 3, color(255, 0, 0));

			g_draw.line(box.left, box.bottom - 1, box.left + (box.right - box.left) / 3, box.bottom - 1, color(255, 0, 0));
			g_draw.line(box.right - (box.right - box.left) / 3 - 1, box.bottom - 1, box.right - 1, box.bottom - 1, color(255, 0, 0));

			g_draw.line(box.left, box.bottom - (box.bottom - box.top) / 3, box.left, box.bottom, color(255, 0, 0));
			g_draw.line(box.right - 1, box.bottom - (box.bottom - box.top) / 3, box.right - 1, box.bottom, color(255, 0, 0));
			break;
		}
		default:
			break;
		}
	}
	if (g_config.settings.visuals.esp.fill_box)
	{
		g_draw.fill_rect(box.left + 1, box.top + 1, box.right - box.left - 2, box.bottom - box.top - 2, color(1, 1, 1, 130));
	}
	if (g_config.settings.visuals.esp.distance)
	{
		g_draw.string(box.right + 3, text_position, color(255, 255, 255), g_draw.esp, false, g_utils.stringer(pentity->get_distance(), "m"));
		text_position += 12;
	}
	if (g_config.settings.visuals.esp.snaplines)
	{
		int width, height;
		g_interfaces.p_engine->get_screen_size(width, height);
		g_draw.line(width / 2, height / 2, box.left + (box.right - box.left) / 2, box.bottom, color(255, 0, 0));
	}
	if (g_config.settings.visuals.esp.name)
	{
		const auto weapon_name = reinterpret_cast<c_base_weapon*>(pentity)->get_weapon_info()->m_weaponname;
		g_draw.string(box.left + (box.right - box.left) / 2, weapon_position, color(255, 255, 255), g_draw.esp, true, g_utils.stringer("[", weapon_name, "]").erase(1, 7));
		weapon_position += 12;
	}
	if (g_config.settings.visuals.esp.ammo)
	{
		if (const auto max_clip = reinterpret_cast<c_base_weapon*>(pentity)->get_weapon_info()->m_maxclip; max_clip != -1)
		{
			const auto iclip = reinterpret_cast<c_base_weapon*>(pentity)->m_iclip1();
			g_draw.string(box.left + (box.right - box.left) / 2, weapon_position, color(255, 255, 255), g_draw.esp, true, g_utils.stringer("[", iclip, "/", max_clip, "]"));
			weapon_position += 12;
		}
	}
}

RECT c_esp::get_boundbox(c_base_entity* p_entity)
{
	RECT box{};

	if (!p_entity)
		return box;

	const matrix3x4_t& trans = p_entity->m_rgflcoordinateframe();
	const auto collision = p_entity->get_collideable();

	if (!collision)
		return box;

	const auto min = collision->obb_mins();
	const auto max = collision->obb_maxs();

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