#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <memory>
#include <thread>
#include <chrono>
#include <map>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <Psapi.h>
#include <fstream> 
#include <thread>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include "../json/json.hpp"
#include "../json/json-forwards.hpp"
#include "utils/vfunc/vfunc.hpp"
#include "config/config.hpp"
#include "math/spoint.hpp"
#include "math/srect.hpp"
#include "../zgui/zgui.hpp"
#include "misc/singleton.hpp"
#include "misc/iappsystem.hpp"
#include "math/vector2d.hpp"
#include "utils/utils.hpp"
#include "misc/color.hpp"
#include "math/qangle.hpp"
#include "math/vector.hpp"
#include "math/vector2d.hpp"
#include "math/vmatrix.hpp"
#include "math/math.hpp"
#include "misc/classid.hpp"
#include "misc/clientclass.hpp"
#include "misc/iappsystem.hpp"
#include "misc/iclientnetworkable.hpp"
#include "misc/recv.hpp"
#include "misc/basehandle.hpp"
#include "misc/icliententity.hpp"
#include "misc/iclientmode.hpp"
#include "misc/iclientnetworkable.hpp"
#include "misc/iclientrenderable.hpp"
#include "misc/iclientthinkable.hpp"
#include "misc/iclientunknown.hpp"
#include "misc/icollideable.hpp"
#include "misc/ihandleentity.hpp"
#include "netvarmanager/netvarmanager.hpp"
#include "misc/baseentity.hpp"

#include "interfaces/valve/globalvars.hpp"
#include "interfaces/valve/ipanel.hpp"
#include "interfaces/valve/isurface.hpp"
#include "utils/drawmanager/drawmanager.hpp"
#include "menu/menu.hpp"
#include "interfaces/valve/ibaseclientdll.hpp"
#include "interfaces/valve/ivengineclient.hpp"
#include "interfaces/valve/icliententitylist.hpp"
#include "interfaces/interfaces.hpp"
#include "utils/vmt/vmt.hpp"
#include "../features/visuals/esp.hpp"

#include "hooks/hooks.hpp"


class c_sdk {
public:
	void on_inject();
	void un_inject();
	bool unhook = false;
	bool esp = false;
};
extern c_sdk g_sdk;






