#include "c_base_weapon.hpp"

weapon_data_t* c_base_weapon::get_weapon_info()
{
	if (!this || this == NULL)
		return NULL;
	 
	return vfunc<454, weapon_data_t*>(this);
}

int c_base_weapon::m_iclip1()
{
	static auto offset = c.netvar->get_offset("DT_BaseCombatWeapon", "m_iClip1");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}