#include "chams.hpp"
c_chams g_chams;

void c_chams::scene_end_start()
{
	if (g_config.settings.visuals.chams.chams)
	{
		static auto chams_material = g_interfaces.p_material_system->findmaterial("debug/debugdrawflat", TEXTURE_GROUP_MODEL);
		
		chams_material->setmaterialvarflag(material_var_ignorez, true);
		chams_material->alphamodulate(1.f);
		chams_material->colormodulate(47 / 255.f, 190 / 255.f ,244 / 255.f);
		
		for (int i = 1; i <= g_interfaces.p_engine->get_max_clients(); i++) {
			const auto p_entity = reinterpret_cast<c_base_entity*>(g_interfaces.p_entity_list->get_client_entity((i)));
			if (!p_entity)
				continue;
			if (p_entity->is_dormant())
				continue;
			if (p_entity == g_interfaces.g_local_player && !g_config.settings.visuals.chams.local)
				continue;

			g_interfaces.p_render_view->setcolormodulation(47 / 255.f, 190 / 255.f, 244 / 255.f);
			g_interfaces.p_model_render->forcedmaterialoverride(chams_material);
			p_entity->draw_model(0x1, 255);
			g_interfaces.p_model_render->forcedmaterialoverride(nullptr);

		}
	}
}
