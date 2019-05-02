#pragma once
#include "../sdk.hpp"
class C_BaseEntity : public IClientEntity
{
public:
	const matrix3x4_t& m_rgflCoordinateFrame();
	int get_index();
	std::string get_name();
	int m_iHealth();
	int m_iAccount();
	int get_distance();
	bool m_bHasHelmet();
	int m_ArmorValue();
	bool is_player();
	bool is_weapon();
	bool is_nade();
	bool is_chicken();
	bool is_c4();
	Vector m_vecOrigin();

};