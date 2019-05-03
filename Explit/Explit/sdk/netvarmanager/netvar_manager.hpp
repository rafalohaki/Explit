#pragma once
#include "../sdk.hpp"

class c_netvarmanager
{
private:
	std::string lasttable = std::string();
public:
	c_netvarmanager();
	~c_netvarmanager();

	uint32_t get_offset(const char* tablename, const char* propname, int change = 0);

	recvvarproxyfn getproxyfunction(const char* tablename, const char* propname);

	void hookprop(const char* tablename, const char* propname, recvvarproxyfn function);

private:
	int get_prop(const char* tablename, const char* propname, recvprop** prop = 0);
	int get_prop(recvtable* recvtable, const char* propname, recvprop** prop = 0);

	recvtable *gettable(const char* tablename);

	std::vector<recvtable*> m_tables;
};

class c_nevtar
{
public:
	std::shared_ptr<c_netvarmanager> netvar = nullptr;
};
extern c_nevtar c;
