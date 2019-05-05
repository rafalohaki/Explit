#include "dlight.hpp"
c_dlight g_dlight;

void c_dlight::start()
{
	if (g_config.settings.visuals.dlights.enable)
	{
		for (int i = 1; i <= g_interfaces.p_engine->get_max_clients(); i++) {
			const auto entity = reinterpret_cast<c_base_entity*>(g_interfaces.p_entity_list->get_client_entity((i)));
			if (!entity)
				continue;
			if (entity->is_dormant())
				continue;
			if (entity == g_interfaces.g_local_player && !g_config.settings.visuals.dlights.local)
				continue;

			if (g_config.settings.visuals.dlights.enemy && entity->m_iteamnum() != g_interfaces.g_local_player->m_iteamnum() && entity->is_valid())
				dlight(entity, { 255,0,0,10 });
			if (g_config.settings.visuals.dlights.team && entity->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() && entity->is_valid())
				dlight(entity, { 0,255,0,10 });

		}
	}
}

void c_dlight::dlight(c_base_entity* pplayer, const colorrgbexp32 color)
{
	auto p_dlight_t = g_interfaces.p_engine_effects->cl_alloc_dlight(pplayer->ent_index());

	p_dlight_t->origin = pplayer->m_vecorigin();
	p_dlight_t->radius = g_config.settings.visuals.dlights.radius;
	p_dlight_t->color = color;
	p_dlight_t->die = g_interfaces.p_global_vars->cur_time + 0.05f;
	p_dlight_t->decay = 200.f;
	p_dlight_t->key = pplayer->ent_index();

}