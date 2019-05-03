#pragma once

#include "../../math/Vector.hpp"
#include "../../math/QAngle.hpp"

typedef unsigned short clientshadowhandle_t;
typedef unsigned short clientrenderhandle_t;
typedef unsigned short modelinstancehandle_t;
typedef unsigned char uint8_t;

class matrix3x4_t;
class i_client_unknown;
struct model_t;

class i_client_renderable
{
public:
	virtual i_client_unknown*          geticlientunknown() = 0;
	virtual Vector const&              getrenderorigin(void) = 0;
	virtual QAngle const&              getrenderangles(void) = 0;
	virtual bool                       shoulddraw(void) = 0;
	virtual int                        getrenderflags(void) = 0; // erenderflags_xxx
	virtual void                       unused(void) const {}
	virtual clientshadowhandle_t       getshadowhandle() const = 0;
	virtual clientrenderhandle_t&      renderhandle() = 0;
	virtual const model_t*             getmodel() const = 0;
	virtual int                        draw_model(int flags, const int /*renderableinstance_t*/ &instance) = 0;
	virtual int                        getbody() = 0;
	virtual void                       getcolormodulation(float* color) = 0;
	virtual bool                       lodtest() = 0;
	virtual bool                       setupbones(matrix3x4_t *pbonetoworldout, int nmaxbones, int bonemask, float currenttime) = 0;
	virtual void                       setupweights(const matrix3x4_t *pbonetoworld, int nflexweightcount, float *pflexweights, float *pflexdelayedweights) = 0;
	virtual void                       doanimationevents(void) = 0;
	virtual void* /*ipvsnotify*/       getpvsnotifyinterface() = 0;
	virtual void                       getrenderbounds(Vector& mins, Vector& maxs) = 0;
	virtual void                       getrenderboundsworldspace(Vector& mins, Vector& maxs) = 0;
	virtual void                       getshadowrenderbounds(Vector &mins, Vector &maxs, int /*shadowtype_t*/ shadowtype) = 0;
	virtual bool                       shouldreceiveprojectedtextures(int flags) = 0;
	virtual bool                       getshadowcastdistance(float *pdist, int /*shadowtype_t*/ shadowtype) const = 0;
	virtual bool                       getshadowcastdirection(Vector *pdirection, int /*shadowtype_t*/ shadowtype) const = 0;
	virtual bool                       isshadowdirty() = 0;
	virtual void                       markshadowdirty(bool bdirty) = 0;
	virtual i_client_renderable*       getshadowparent() = 0;
	virtual i_client_renderable*       firstshadowchild() = 0;
	virtual i_client_renderable*       nextshadowpeer() = 0;
	virtual int /*shadowtype_t*/       shadowcasttype() = 0;
	virtual void                       createmodelinstance() = 0;
	virtual modelinstancehandle_t      getmodelinstance() = 0;
	virtual const matrix3x4_t&         renderabletoworldtransform() = 0;
	virtual int                        lookupattachment(const char *pattachmentname) = 0;
	virtual   bool                     getattachment(int number, Vector &origin, QAngle &angles) = 0;
	virtual bool                       getattachment(int number, matrix3x4_t &matrix) = 0;
	virtual float*                     getrenderclipplane(void) = 0;
	virtual int                        getskin() = 0;
	virtual void                       onthreadeddrawsetup() = 0;
	virtual bool                       usesflexdelayedweights() = 0;
	virtual void                       recordtoolmessage() = 0;
	virtual bool                       shoulddrawforsplitscreenuser(int nslot) = 0;
	virtual uint8_t                    overridealphamodulation(uint8_t nalpha) = 0;
	virtual uint8_t                    overrideshadowalphamodulation(uint8_t nalpha) = 0;
};