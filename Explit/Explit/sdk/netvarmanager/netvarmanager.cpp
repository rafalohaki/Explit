#include "netvarmanager.hpp"

c_nevtar c;

c_netvarmanager::c_netvarmanager()
{
	m_tables.clear();

	ClientClass* clientClass = g_interfaces.p_client->GetAllClasses();
	if (!clientClass)
		return;

	while (clientClass)
	{
		RecvTable* recvTable = clientClass->pRecvTable;

		m_tables.push_back(recvTable);

		clientClass = clientClass->pNext;
	}
}

c_netvarmanager::~c_netvarmanager()
{
	m_tables.clear();
}

void c_netvarmanager::GetOffset(const char *tableName, const char *propName, unsigned long* pOffset, int change)
{
	int offset = Get_Prop(tableName, propName);
	int roffset = offset + change;
	if (offset)
		*pOffset = roffset;

	if (lastTable.compare(tableName))
	{
		std::cout << tableName << ":" << std::endl;
		lastTable = tableName;
	}

	std::cout << " |__" << propName << " - 0x" << (DWORD*)roffset << std::endl;
}
uint32_t c_netvarmanager::Get_Offset(const char *tableName, const char *propName, int change)
{
	int offset = Get_Prop(tableName, propName);
	int roffset = offset + change;
	if (offset)
		return roffset;

	if (lastTable.compare(tableName))
	{
		std::cout << tableName << ":" << std::endl;
		lastTable = tableName;
	}

	std::cout << " |__" << propName << " - 0x" << (DWORD*)roffset << std::endl;
}

RecvVarProxyFn c_netvarmanager::GetProxyFunction(const char *tableName, const char *propName)
{
	RecvProp* recvProp = nullptr;
	Get_Prop(tableName, propName, &recvProp);
	if (!recvProp)
		return nullptr;

	return recvProp->GetProxyFn();
}

void c_netvarmanager::HookProp(const char *tableName, const char *propName, RecvVarProxyFn function)
{
	RecvProp* recvProp = nullptr;
	Get_Prop(tableName, propName, &recvProp);
	if (!recvProp)
		return;

	recvProp->SetProxyFn(function); //recvProp->m_ProxyFn = function;
}

int c_netvarmanager::Get_Prop(const char *tableName, const char *propName, RecvProp **prop)
{
	RecvTable* recvTable = GetTable(tableName);
	if (!recvTable)
		return 0;

	int offset = Get_Prop(recvTable, propName, prop);
	if (!offset)
		return 0;

	return offset;
}

int c_netvarmanager::Get_Prop(RecvTable *recvTable, const char *propName, RecvProp **prop)
{
	int extraOffset = 0;

	for (int i = 0; i < recvTable->nProps; ++i)
	{
		RecvProp* recvProp = &recvTable->pProps[i];
		RecvTable* child = recvProp->GetDataTable();

		if (child && (child->nProps > 0))
		{
			int tmp = Get_Prop(child, propName, prop);

			if (tmp)
				extraOffset += (recvProp->GetOffset() + tmp);
		}

		if (_stricmp(recvProp->pVarName, propName))
			continue;

		if (prop)
			*prop = recvProp;

		return (recvProp->GetOffset() + extraOffset);
	}

	return extraOffset;
}

RecvTable* c_netvarmanager::GetTable(const char *tableName)
{
	if (m_tables.empty())
		return 0;

	for each (RecvTable* table in m_tables)
	{
		if (!table)
			continue;

		if (_stricmp(table->pNetTableName, tableName) == 0)
			return table;
	}

	return 0;
}