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
			draw_weapons(glow_entity);
		if (g_config.settings.visuals.glow.chickens && pentity->is_chicken())
			draw_chickens(glow_entity);
		if (g_config.settings.visuals.glow.enemy && pentity->m_iteamnum() != g_interfaces.g_local_player->m_iteamnum() && pentity->is_valid())
			draw_players(glow_entity);
		if (g_config.settings.visuals.glow.team && pentity->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() && pentity->is_valid())
			draw_players(glow_entity);
	}
}
void c_glow::draw_chickens(c_glow_manager::glow_object_definition_t* glow_entity)
{
	glow_entity->red = 0;
	glow_entity->green = 0;
	glow_entity->blue = 255;
	glow_entity->alpha = 255;

	glow_entity->glow_style = g_config.settings.visuals.glow.style;

	glow_entity->render_when_occluded = true;
	glow_entity->render_when_unoccluded = false;
}
void c_glow::draw_weapons(c_glow_manager::glow_object_definition_t* glow_entity)
{
	glow_entity->red = 0;
	glow_entity->green = 255;
	glow_entity->blue = 0;
	glow_entity->alpha = 255;

	glow_entity->glow_style = g_config.settings.visuals.glow.style;

	glow_entity->render_when_occluded = true;
	glow_entity->render_when_unoccluded = false;
}
void c_glow::draw_players(c_glow_manager::glow_object_definition_t* glow_entity)
{
	glow_entity->red = 0;
	glow_entity->green = 255;
	glow_entity->blue = 255;
	glow_entity->alpha = 255;

	glow_entity->glow_style = g_config.settings.visuals.glow.style;

	glow_entity->render_when_occluded = true;
	glow_entity->render_when_unoccluded = false;
}