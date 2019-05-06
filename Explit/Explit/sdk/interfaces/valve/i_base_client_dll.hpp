#pragma once
#include "i_global_vars.hpp"
#include "../../misc/valve/client_class.hpp"
#include "../../misc/valve/i_app_system.hpp"

class i_base_client_dll
{
public:
	virtual int              connect(createinterfacefn app_system_factory, i_global_vars_base *p_globals) = 0;
	virtual int              disconnect(void) = 0;
	virtual int              init(createinterfacefn app_system_factory, i_global_vars_base *p_globals) = 0;
	virtual void             post_init() = 0;
	virtual void             shutdown(void) = 0;
	virtual void             level_init_pre_entity(char const* p_map_name) = 0;
	virtual void             level_init_post_entity() = 0;
	virtual void             level_shutdown(void) = 0;
	virtual client_class*    get_all_classes(void) = 0;
};