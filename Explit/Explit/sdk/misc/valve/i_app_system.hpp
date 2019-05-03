#pragma once

typedef void* (*createinterfacefn)(const char *pname, int *preturncode);
typedef void* (*instantiateinterfacefn)();

class i_app_system
{
public:
	virtual bool                            connect(createinterfacefn factory) = 0;                                     // 0
	virtual void                            disconnect() = 0;                                                           // 1
	virtual void*                           query_interface(const char *pinterfacename) = 0;                             // 2
	virtual int /*initreturnval_t*/         init() = 0;                                                                 // 3
	virtual void                            shutdown() = 0;                                                             // 4
	virtual const void* /*appsysteminfo_t*/ get_dependencies() = 0;                                                      // 5
	virtual int /*appsystemtier_t*/         get_tier() = 0;                                                              // 6
	virtual void                            reconnect(createinterfacefn factory, const char *pinterfacename) = 0;       // 7
	virtual void                            unkfunc() = 0;                                                              // 8
};