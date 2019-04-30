#pragma once
#include "../sdk.hpp"

class c_netvarmanager
{
private:
	std::string lastTable = std::string();
public:
	c_netvarmanager();
	~c_netvarmanager();

	void GetOffset(const char* tableName, const char* propName, unsigned long* pOffset, int change = 0);

	uint32_t Get_Offset(const char* tableName, const char* propName, int change = 0);

	RecvVarProxyFn GetProxyFunction(const char* tableName, const char* propName);

	void HookProp(const char* tableName, const char* propName, RecvVarProxyFn function);

private:
	int Get_Prop(const char* tableName, const char* propName, RecvProp** prop = 0);
	int Get_Prop(RecvTable* recvTable, const char* propName, RecvProp** prop = 0);

	RecvTable *GetTable(const char* tableName);

	std::vector<RecvTable*> m_tables;
};

class c_nevtar
{
public:
	std::shared_ptr<c_netvarmanager> netvar = nullptr;
};
extern c_nevtar c;
