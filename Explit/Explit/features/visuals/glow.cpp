#include "glow.hpp"
c_glow g_glow;

void c_glow::start()
{
	static auto glow_object_manager = *(c_glow_manager**)(g_utils.find_signature("client_panorama.dll", "0F 11 05 ? ? ? ? 83 C8 01 C7 05 ? ? ? ? 00 00 00 00") + 3);

	for (int i = 0; i < glow_object_manager->size; i++)
	{
		c_glow_manager::glow_object_definition_t* glow_entity = &glow_object_manager->glow_object_definitions[i];

		const auto pentity = glow_entity->pentity;

		if (!pentity)
			continue;
		if (pentity->is_dormant())
			continue;
		if (pentity == g_interfaces.g_local_player && !g_config.settings.visuals.glow.local)
			continue;

		if (g_config.settings.visuals.glow.weapons && pentity->is_weapon())
			glow(glow_entity,color(g_config.settings.visuals.glow.colors.weapons[0], g_config.settings.visuals.glow.colors.weapons[1], g_config.settings.visuals.glow.colors.weapons[2]));
		if (g_config.settings.visuals.glow.chickens && pentity->is_chicken())
			glow(glow_entity, color(g_config.settings.visuals.glow.colors.chickens[0], g_config.settings.visuals.glow.colors.chickens[1], g_config.settings.visuals.glow.colors.chickens[2]));
		if (g_config.settings.visuals.glow.enemy && pentity->m_iteamnum() != g_interfaces.g_local_player->m_iteamnum() && pentity->is_valid())
			glow(glow_entity, color(g_config.settings.visuals.glow.colors.enemy_visible[0], g_config.settings.visuals.glow.colors.enemy_visible[1], g_config.settings.visuals.glow.colors.enemy_visible[2]));
		if (g_config.settings.visuals.glow.team && pentity->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() && pentity->is_valid())
			glow(glow_entity, color(g_config.settings.visuals.glow.colors.team_visible[0], g_config.settings.visuals.glow.colors.team_visible[1], g_config.settings.visuals.glow.colors.team_visible[2]));
	}
}
void c_glow::glow(c_glow_manager::glow_object_definition_t* glow_entity, const color c)
{
	glow_entity->red = c.r();
	glow_entity->green = c.g();
	glow_entity->blue = c.b();
	glow_entity->alpha = 255;

	glow_entity->glow_style = g_config.settings.visuals.glow.style;

	glow_entity->render_when_occluded = true;
	glow_entity->render_when_unoccluded = false;
}
