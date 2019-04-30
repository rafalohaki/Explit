#pragma once
#include "recv.hpp"
#include "classid.hpp"
#include "iclientnetworkable.hpp"

class ClientClass;

typedef IClientNetworkable*   (*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable*   (*CreateEventFn)();

class ClientClass
{
public:
	CreateClientClassFn      pCreateFn;
	CreateEventFn            pCreateEventFn;
	char*                    pNetworkName;
	RecvTable*               pRecvTable;
	ClientClass*             pNext;
	ClassID					 ClassID;
};