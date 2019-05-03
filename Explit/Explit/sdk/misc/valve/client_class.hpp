#pragma once
#include "recv.hpp"
#include "class_id.hpp"
#include "i_client_networkable.hpp"

class client_class;

typedef i_client_networkable*   (*createclientclassfn)(int entnum, int serialnum);
typedef i_client_networkable*   (*createeventfn)();

class client_class
{
public:
	createclientclassfn      pcreate_fn;
	createeventfn            pcreate_event_fn;
	char*                    pnetwork_name;
	recvtable*               precv_table;
	client_class*            pnext;
	class_id				 class_id;
};