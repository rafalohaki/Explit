#pragma once

class i_client_unknown;
class client_class;
class bf_read;

class i_client_networkable
{
public:
	virtual i_client_unknown* geticlientunknown() = 0;
	virtual void             release() = 0;
	virtual client_class*    get_client_class() = 0;
	virtual void             notifyshouldtransmit(int state) = 0;
	virtual void             onpredatachanged(int updatetype) = 0;
	virtual void             ondatachanged(int updatetype) = 0;
	virtual void             predataupdate(int updatetype) = 0;
	virtual void             postdataupdate(int updatetype) = 0;
	virtual void             __unkn(void) = 0;
	virtual bool             is_dormant(void) = 0;
	virtual int              entindex(void) const = 0;
	virtual void             receivemessage(int classid, bf_read& msg) = 0;
	virtual void*            getdatatablebaseptr() = 0;
	virtual void             setdestroyedonrecreateentities(void) = 0;
};