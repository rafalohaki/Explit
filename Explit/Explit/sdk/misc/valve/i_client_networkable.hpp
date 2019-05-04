#pragma once

class i_client_unknown;
class client_class;
class bf_read;

class i_client_networkable
{
public:
	virtual i_client_unknown* get_i_client_unknown() = 0;
	virtual void             release() = 0;
	virtual client_class*    get_client_class() = 0;
	virtual void             notify_should_transmit(int state) = 0;
	virtual void             on_predata_changed(int updatetype) = 0;
	virtual void             on_data_changed(int updatetype) = 0;
	virtual void             predata_update(int updatetype) = 0;
	virtual void             postdata_update(int updatetype) = 0;
	virtual void             __unkn(void) = 0;
	virtual bool             is_dormant(void) = 0;
	virtual int              ent_index(void) const = 0;
	virtual void             receive_message(int classid, bf_read& msg) = 0;
	virtual void*            get_data_table_base_ptr() = 0;
	virtual void             set_destroyed_on_recreate_entities(void) = 0;
};