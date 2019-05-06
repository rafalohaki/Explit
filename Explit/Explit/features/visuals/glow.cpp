#include "glow.hpp"
c_glow g_glow;

void c_glow::start()
{
	static auto glow_object_manager = *(c_glow_manager**)(g_utils.find_signature("client_panorama.dll", "0F 11 05 ? ? ? ? 83 C8 01 C7 05 ? ? ? ? 00 00 00 00") + 3);

	for (int i = 0; i < glow_object_manager->size; i++)
	{
		c_glow_manager::glow_object_definition_t* p_glow_entity = &glow_object_manager->glow_object_definitions[i];

		const auto p_entity = p_glow_entity->p_entity;

		if (!p_entity)
			continue;
		if (p_entity->is_dormant())
			continue;
		if (p_entity == g_interfaces.g_local_player && !g_config.settings.visuals.glow.local)
			continue;

		if (g_config.settings.visuals.glow.weapons && p_entity->is_weapon())
			glow(p_glow_entity,color(g_config.settings.visuals.glow.colors.weapons[0], g_config.settings.visuals.glow.colors.weapons[1], g_config.settings.visuals.glow.colors.weapons[2]));
		if (g_config.settings.visuals.glow.chickens && p_entity->is_chicken())
			glow(p_glow_entity, color(g_config.settings.visuals.glow.colors.chickens[0], g_config.settings.visuals.glow.colors.chickens[1], g_config.settings.visuals.glow.colors.chickens[2]));
		if (g_config.settings.visuals.glow.enemy && p_entity->m_iteamnum() != g_interfaces.g_local_player->m_iteamnum() && p_entity->is_valid())
			glow(p_glow_entity, color(g_config.settings.visuals.glow.colors.enemy_visible[0], g_config.settings.visuals.glow.colors.enemy_visible[1], g_config.settings.visuals.glow.colors.enemy_visible[2]));
		if (g_config.settings.visuals.glow.team && p_entity->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() && p_entity->is_valid())
			glow(p_glow_entity, color(g_config.settings.visuals.glow.colors.team_visible[0], g_config.settings.visuals.glow.colors.team_visible[1], g_config.settings.visuals.glow.colors.team_visible[2]));
	}
}

void c_glow::glow(c_glow_manager::glow_object_definition_t* p_glow_entity, const color color)
{
	p_glow_entity->red = color.r();
	p_glow_entity->green = color.g();
	p_glow_entity->blue = color.b();
	p_glow_entity->alpha = 255;

	p_glow_entity->glow_style = g_config.settings.visuals.glow.style;

	p_glow_entity->render_when_occluded = true;
	p_glow_entity->render_when_unoccluded = false;
}
