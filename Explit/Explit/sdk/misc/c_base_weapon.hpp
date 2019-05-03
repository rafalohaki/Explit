#pragma once
#include "../sdk.hpp"

class weapon_data_t
{
public:
	char pad_0x0000[0x4]; //0x0000
	char* m_weaponname; //0x0004 
	char pad_0x0008[0xc]; //0x0008
	__int32 m_maxclip; //0x0014 
	char pad_0x0018[0xc]; //0x0018
	__int32 m_maxreservedammo; //0x0024 
	char pad_0x0028[0x4]; //0x0028
	char* m_weaponmdlpath; //0x002c 
	char pad_0x0030[0x4]; //0x0030
	char* m_dropweaponmdlpath; //0x0034 
	char pad_0x0038[0x48]; //0x0038
	char* m_bullettype; //0x0080 
	char pad_0x0084[0x4]; //0x0084
	char* m_weaponhudname; //0x0088 
	char pad_0x008c[0x40]; //0x008c
	__int32 m_weapontype; //0x00cc 
	__int32 m_weaponprice; //0x00d0 
	__int32 m_weaponreward; //0x00d4 
	char* m_weapongroupname; //0x00d8 
	char pad_0x00dc[0x10]; //0x00dc
	unsigned char m_fullauto; //0x00ec 
	char pad_0x00ed[0x3]; //0x00ed
	__int32 m_weapondamage; //0x00f0 
	float m_armorratio; //0x00f4 
	__int32 m_ibullets;
	float m_penetration; //0x00f8
	char pad_0x00f8[0x8]; //0x00fc
	float m_weaponrange; //0x0108 
	float m_rangemodifier; //0x010c 
	char pad_0x0110[0x10]; //0x0110
	unsigned char m_hassilencer; //0x0120 
	char pad_0x0121[0xf]; //0x0121
	float m_maxspeed; //0x0130 
	float m_maxspeed2; //0x0134 
	char pad_0x0138[0x4c]; //0x0138
	__int32 m_recoilseed; //0x0184 
	char pad_0x0188[0x68]; //0x0188
	char* m_weapontracestype; //0x01f0 
	char pad_0x01f4[0x638]; //0x01f4

}; //Size=0x082C


class c_base_weapon
{
public:
	weapon_data_t* get_weapon_info();
	int m_iclip1();
};

