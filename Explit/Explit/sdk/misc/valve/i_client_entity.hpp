#pragma once 

#include "i_client_networkable.hpp"
#include "i_client_renderable.hpp"
#include "i_client_unknown.hpp"
#include "i_client_thinkable.hpp"

struct spatializationinfo_t;

class i_client_entity : public i_client_unknown, public i_client_renderable, public i_client_networkable, public i_client_thinkable
{
public:
	virtual void release(void) = 0;
	virtual const Vector &get_abs_origin(void) const = 0;
	virtual const QAngle &get_abs_angles(void) const = 0;
};