#pragma once
#include "i_global_vars.hpp"
#include "../../misc/valve/client_class.hpp"
#include "../../misc/valve/i_app_system.hpp"

class i_base_client_dll
{
public:
	virtual int              connect(createinterfacefn appsystemfactory, i_global_vars_base *pglobals) = 0;
	virtual int              disconnect(void) = 0;
	virtual int              init(createinterfacefn appsystemfactory, i_global_vars_base *pglobals) = 0;
	virtual void             postinit() = 0;
	virtual void             shutdown(void) = 0;
	virtual void             levelinitpreentity(char const* pmapname) = 0;
	virtual void             levelinitpostentity() = 0;
	virtual void             levelshutdown(void) = 0;
	virtual client_class*    getallclasses(void) = 0;
};