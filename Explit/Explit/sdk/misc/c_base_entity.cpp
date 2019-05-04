#include "c_base_entity.hpp"

const matrix3x4_t& c_base_entity::m_rgflcoordinateframe()
{
	static auto offset = c.netvar->get_offset("DT_BaseEntity","m_CollisionGroup", -0x30);
	return *(matrix3x4_t*)((uintptr_t)this + offset);
}
Vector c_base_entity::m_vecorigin()
{
	static auto offset = c.netvar->get_offset("DT_BaseEntity", "m_vecOrigin");
	return *reinterpret_cast<Vector*>((uintptr_t)this + offset);
}
int c_base_entity::get_index()
{
	return *reinterpret_cast<int*>((uintptr_t)this + 0x64);
}
std::string c_base_entity::get_name()
{
	player_info_t info;
	g_interfaces.p_engine->getplayerinfo(this->get_index(), &info);
	return info.szname;
}
int c_base_entity::m_howner()
{
	return *reinterpret_cast<int*>((uintptr_t)this + 0x148);
}
int c_base_entity::m_iteamnum()
{
	static auto offset = c.netvar->get_offset("DT_BaseEntity", "m_iTeamNum");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}
int c_base_entity::m_ihealth()
{
	static auto offset = c.netvar->get_offset("DT_BasePlayer", "m_iHealth");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}
int c_base_entity::m_iaccount()
{
	static auto offset = c.netvar->get_offset("DT_CSPlayer", "m_iAccount");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}
int c_base_entity::get_distance()
{
	const auto local_origin = g_interfaces.g_local_player->m_vecorigin();
	const auto player_origin = this->m_vecorigin();
	return static_cast<int>(sqrt(pow(local_origin.x - player_origin.x, 2) + pow(local_origin.y - player_origin.y, 2) + pow(local_origin.z - player_origin.z, 2)) * 0.0254f);
}
bool c_base_entity::m_bhashelmet()
{
	static auto offset = c.netvar->get_offset("DT_CSPlayer", "m_bHasHelmet");
	return *reinterpret_cast<bool*>((uintptr_t)this + offset);
}
c_base_handle c_base_entity::m_hactiveweapon()
{
	static auto offset = c.netvar->get_offset("DT_BasePlayer", "m_hActiveWeapon");
	return *reinterpret_cast<c_base_handle*>((uintptr_t)this + offset);
}
c_base_weapon* c_base_entity::get_weapon()
{
	return (c_base_weapon*)g_interfaces.p_entity_list->get_client_entity_from_handle((c_base_handle)m_hactiveweapon());
}
int c_base_entity::m_armorvalue()
{
	static auto offset = c.netvar->get_offset("DT_CSPlayer", "m_ArmorValue");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}
int32_t c_base_entity::m_ilifestate()
{
	static auto offset = c.netvar->get_offset("DT_BasePlayer", "m_lifeState");
	return *reinterpret_cast<int32_t*>((uintptr_t)this + offset);
}
bool c_base_entity::is_valid()
{
	return (is_player() && !is_dormant() && m_ilifestate() == life_alive);
}
bool c_base_entity::is_player()
{
	return vfunc<155, bool>(this);
}
bool c_base_entity::is_weapon()
{
	return vfunc<163, bool>(this);
}
bool c_base_entity::is_nade()
{
	return false;
}
bool c_base_entity::is_chicken()
{
	return get_client_class()->class_id == class_id::cchicken;
}
bool c_base_entity::is_c4()
{
	return get_client_class()->class_id == class_id::cplantedc4 || get_client_class()->class_id == class_id::cc4;
}