#pragma once

class i_client_unknown;
class cclientthinkhandleptr;
typedef cclientthinkhandleptr* clientthinkhandle_t;

class i_client_thinkable
{
public:
	virtual i_client_unknown*   get_i_client_unknown() = 0;
	virtual void                client_think() = 0;
	virtual clientthinkhandle_t get_think_handle() = 0;
	virtual void                set_think_handle(clientthinkhandle_t hthink) = 0;
	virtual void                release() = 0;
};