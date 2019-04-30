#include "baseentity.hpp"

const matrix3x4_t& C_BaseEntity::m_rgflCoordinateFrame()
{
	static auto offset = c.netvar->Get_Offset("DT_BaseEntity","m_CollisionGroup", -0x30);
	return *(matrix3x4_t*)((uintptr_t)this + offset);
}

ICollideable* C_BaseEntity::get_collideable()
{
	//typedef ICollideable*(__thiscall *OrigFn)(void*);
	return vfunc<3, ICollideable*>(this);

}
Vector C_BaseEntity::m_vecOrigin()
{
	static auto offset = c.netvar->Get_Offset("DT_BaseEntity", "m_vecOrigin");
	return *reinterpret_cast<Vector*>((uintptr_t)this + offset);
}
bool C_BaseEntity::is_player()
{
	return vfunc<153, bool>(this);
}
bool C_BaseEntity::is_weapon()
{
	return vfunc<161, bool>(this);
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