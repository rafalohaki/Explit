#pragma once
class i_global_vars_base 
{
public:
	float     real_time;
	int       frame_count;
	float     absolute_frame_time;
	float     absolute_frame_start_time_stddev;
	float     cur_time;
	float     frame_time;
	int       max_clients;
	int       tick_count;
	float     interval_per_tick;
	float     interpolation_amount;
	int       sim_ticks_this_frame;
	int       network_protocol;
	void*     psavedata;
	bool      bclient;
	bool      bremote_client;

private:
	// 100 (i.e., tickcount is rounded down to this base and then the "delta" from this base is networked
	int       ntime_stamp_networking_base;
	// 32 (entindex() % ntimestamprandomizewindow ) is subtracted from gpglobals->tickcount to set the networking basis, prevents
	//  all of the entities from forcing a new packedentity on the same tick (i.e., prevents them from getting lockstepped on this)
	int       ntime_stamp_randomize_window;
};
