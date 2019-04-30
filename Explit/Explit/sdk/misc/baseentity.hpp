#pragma once
#include "../sdk.hpp"
class C_BaseEntity : public IClientEntity
{
public:
	const matrix3x4_t& m_rgflCoordinateFrame();
	ICollideable* get_collideable();
	bool is_player();
	bool is_weapon();
	bool is_nade();
	bool is_chicken();
	bool is_c4();
	Vector m_vecOrigin();
	//NETVAR(int32_t, m_iTeamNum, "CBaseEntity", "m_iTeamNum");


	//NETVAR(Vector, m_vecVelocity, "CBasePlayer", "m_vecVelocity[0]");
	//NETVAR(Vector, m_vecViewOffset, "CBasePlayer", "m_vecViewOffset[0]");
	//NETVAR(int32_t, m_iHealth, "CBasePlayer", "m_iHealth");
	//NETVAR(int32_t, m_lifeState, "CBasePlayer", "m_lifeState");
	//NETVAR(int32_t, m_fFlags, "CBasePlayer", "m_fFlags");

};