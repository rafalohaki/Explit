#include "netvar_manager.hpp"

c_nevtar c;

c_netvarmanager::c_netvarmanager()
{
	m_tables.clear();

	client_class* client_class = g_interfaces.p_client->getallclasses();
	if (!client_class)
		return;

	while (client_class)
	{
		recvtable* recvtable = client_class->precv_table;

		m_tables.push_back(recvtable);

		client_class = client_class->pnext;
	}
}

c_netvarmanager::~c_netvarmanager()
{
	m_tables.clear();
}

uint32_t c_netvarmanager::get_offset(const char *tablename, const char *propname, int change)
{
	int offset = get_prop(tablename, propname);
	int roffset = offset + change;
	if (offset)
		return roffset;

	if (lasttable.compare(tablename))
	{
		lasttable = tablename;
	}

}

recvvarproxyfn c_netvarmanager::getproxyfunction(const char *tablename, const char *propname)
{
	recvprop* recvprop = nullptr;
	get_prop(tablename, propname, &recvprop);
	if (!recvprop)
		return nullptr;

	return recvprop->getproxyfn();
}

void c_netvarmanager::hookprop(const char *tablename, const char *propname, recvvarproxyfn function)
{
	recvprop* recvprop = nullptr;
	get_prop(tablename, propname, &recvprop);
	if (!recvprop)
		return;

	recvprop->setproxyfn(function); //recvprop->m_proxyfn = function;
}

int c_netvarmanager::get_prop(const char *tablename, const char *propname, recvprop **prop)
{
	recvtable* recvtable = gettable(tablename);
	if (!recvtable)
		return 0;

	int offset = get_prop(recvtable, propname, prop);
	if (!offset)
		return 0;

	return offset;
}

int c_netvarmanager::get_prop(recvtable *recv_table, const char *propname, recvprop **prop)
{
	int extraoffset = 0;

	for (int i = 0; i < recv_table->nprops; ++i)
	{
		recvprop* recvprop = &recv_table->pprops[i];
		recvtable* child = recvprop->getdatatable();

		if (child && (child->nprops > 0))
		{
			int tmp = get_prop(child, propname, prop);

			if (tmp)
				extraoffset += (recvprop->getoffset() + tmp);
		}

		if (_stricmp(recvprop->pvarname, propname))
			continue;

		if (prop)
			*prop = recvprop;

		return (recvprop->getoffset() + extraoffset);
	}

	return extraoffset;
}

recvtable* c_netvarmanager::gettable(const char *tablename)
{
	if (m_tables.empty())
		return 0;

	for each (recvtable* table in m_tables)
	{
		if (!table)
			continue;

		if (_stricmp(table->pnettablename, tablename) == 0)
			return table;
	}

	return 0;
}