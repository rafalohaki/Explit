#include "baseentity.hpp"

const matrix3x4_t& C_BaseEntity::m_rgflCoordinateFrame()
{
	static auto offset = c.netvar->Get_Offset("DT_BaseEntity","m_CollisionGroup", -0x30);
	return *(matrix3x4_t*)((uintptr_t)this + offset);
}
Vector C_BaseEntity::m_vecOrigin()
{
	static auto offset = c.netvar->Get_Offset("DT_BaseEntity", "m_vecOrigin");
	return *reinterpret_cast<Vector*>((uintptr_t)this + offset);
}
int C_BaseEntity::get_index()
{
	return *reinterpret_cast<int*>((uintptr_t)this + 0x64);
}
std::string C_BaseEntity::get_name()
{
	player_info_t info;
	g_interfaces.p_engine->GetPlayerInfo(this->get_index(), &info);
	return info.szName;
}
int C_BaseEntity::m_iHealth()
{
	static auto offset = c.netvar->Get_Offset("DT_BasePlayer", "m_iHealth");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}
int C_BaseEntity::m_iAccount()
{
	static auto offset = c.netvar->Get_Offset("DT_CSPlayer", "m_iAccount");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}
int C_BaseEntity::get_distance()
{
	const auto local_origin = g_interfaces.g_localplayer->m_vecOrigin();
	const auto player_origin = this->m_vecOrigin();
	return static_cast<int>(sqrt(pow(local_origin.x - player_origin.x, 2) + pow(local_origin.y - player_origin.y, 2) + pow(local_origin.z - player_origin.z, 2)) * 0.0254f);
}
bool C_BaseEntity::m_bHasHelmet()
{
	static auto offset = c.netvar->Get_Offset("DT_CSPlayer", "m_bHasHelmet");
	return *reinterpret_cast<bool*>((uintptr_t)this + offset);
}
int C_BaseEntity::m_ArmorValue()
{
	static auto offset = c.netvar->Get_Offset("DT_CSPlayer", "m_ArmorValue");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}
bool C_BaseEntity::is_player()
{
	return vfunc<155, bool>(this);
}
bool C_BaseEntity::is_weapon()
{
	return vfunc<163, bool>(this);
}
bool C_BaseEntity::is_nade()
{
	return false;
}
bool C_BaseEntity::is_chicken() 
{
	return GetClientClass()->ClassID == ClassID::CChicken;
}
bool C_BaseEntity::is_c4()
{
	return GetClientClass()->ClassID == ClassID::CPlantedC4 || GetClientClass()->ClassID == ClassID::CC4;
}