#pragma once 

#include "iclientnetworkable.hpp"
#include "iclientrenderable.hpp"
#include "iclientunknown.hpp"
#include "iclientthinkable.hpp"

struct SpatializationInfo_t;

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual void Release(void) = 0;
	virtual const Vector &GetAbsOrigin(void) const = 0;
	virtual const QAngle &GetAbsAngles(void) const = 0;
};