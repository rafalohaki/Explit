#pragma once
#include "../../sdk.hpp"

class c_phys_collide;
class c_utl_buffer;
class i_client_renderable;
class c_studio_hrd;
struct virtual_model_t;

enum renderable_translucency_type_t
{
	renderable_is_opaque = 0,
	renderable_is_translucent,
	renderable_is_two_pass,    // has both translucent and opaque sub-partsa
};

class ivmodelinfo
{
public:
	virtual                                 ~ivmodelinfo(void) {}
	virtual const model_t*                  getmodel(int modelindex) const = 0;
	virtual int                             getmodelindex(const char *name) const = 0;
	virtual const char*                     getmodelname(const model_t *model) const = 0;
	virtual void							unused() {};
	virtual v_collide_t*                     getvcollide(const model_t *model) const = 0;
	virtual v_collide_t*                     getvcollide(int modelindex) const = 0;
	virtual void                            getmodelbounds(const model_t *model, Vector& mins, Vector& maxs) const = 0;
	virtual void                            getmodelrenderbounds(const model_t *model, Vector& mins, Vector& maxs) const = 0;
	virtual int                             getmodelframecount(const model_t *model) const = 0;
	virtual int                             getmodeltype(const model_t *model) const = 0;
	virtual void*                           getmodelextradata(const model_t *model) = 0;
	virtual bool                            modelhasmaterialproxy(const model_t *model) const = 0;
	virtual bool                            istranslucent(model_t const* model) const = 0;
	virtual bool                            istranslucenttwopass(const model_t *model) const = 0;
	virtual void                            unused0() {};
	virtual renderable_translucency_type_t    computetranslucencytype(const model_t *model, int nskin, int nbody) = 0;
	virtual int                             getmodelmaterialcount(const model_t* model) const = 0;
	virtual void                            getmodelmaterials(const model_t *model, int count, i_material** ppmaterial) = 0;
	virtual bool                            ismodelvertexlit(const model_t *model) const = 0;
	virtual const char*                     getmodelkeyvaluetext(const model_t *model) = 0;
	virtual bool                            getmodelkeyvalue(const model_t *model, c_utl_buffer &buf) = 0;
	virtual float                           getmodelradius(const model_t *model) = 0;
	virtual c_studio_hrd*                     getstudiohdr(mdl_handle_t handle) = 0;
	virtual const studio_hdr_t*              findmodel(const studio_hdr_t *pstudiohdr, void **cache, const char *modelname) const = 0;
	virtual const studio_hdr_t*              findmodel(void *cache) const = 0;
	virtual virtual_model_t*                 getvirtualmodel(const studio_hdr_t *pstudiohdr) const = 0;
	virtual uint8_t*                        getanimblock(const studio_hdr_t *pstudiohdr, int iblock) const = 0;
	virtual void                            getmodelmaterialcolorandlighting(const model_t *model, Vector const& origin, QAngle const& angles, trace_t* ptrace, Vector& lighting, Vector& matcolor) = 0;
	virtual void                            getilluminationpoint(const model_t *model, i_client_renderable *prenderable, Vector const& origin, QAngle const& angles, Vector* plightingcenter) = 0;
	virtual int                             getmodelcontents(int modelindex) const = 0;
	virtual void							unused11() {};
	virtual studio_hdr_t                    *getstudiomodel(const model_t *mod) = 0;
	virtual int                             getmodelspritewidth(const model_t *model) const = 0;
	virtual int                             getmodelspriteheight(const model_t *model) const = 0;
	virtual void                            setlevelscreenfaderange(float flminsize, float flmaxsize) = 0;
	virtual void                            getlevelscreenfaderange(float *pminarea, float *pmaxarea) const = 0;
	virtual void                            setviewscreenfaderange(float flminsize, float flmaxsize) = 0;
	virtual unsigned char                   computelevelscreenfade(const Vector &vecabsorigin, float flradius, float flfadescale) const = 0;
	virtual unsigned char                   computeviewscreenfade(const Vector &vecabsorigin, float flradius, float flfadescale) const = 0;
	virtual int                             getautoplaylist(const studio_hdr_t *pstudiohdr, unsigned short **pautoplaylist) const = 0;
	virtual c_phys_collide*                   getcollideforvirtualterrain(int index) = 0;
	virtual bool                            isusingfbtexture(const model_t *model, int nskin, int nbody, i_client_renderable* *pclientrenderable) const = 0;
	virtual const model_t*                  findorloadmodel(const char *name) const = 0;
	virtual mdl_handle_t                     getcachehandle(const model_t *model) const = 0;
	virtual int                             getbrushmodelplanecount(const model_t *model) const = 0;
	virtual void                            getbrushmodelplane(const model_t *model, int nindex, c_plane_t &plane, Vector *porigin) const = 0;
	virtual int                             getsurfacepropsforvirtualterrain(int index) = 0;
	virtual bool                            usesenvcubemap(const model_t *model) const = 0;
	virtual bool                            usesstaticlighting(const model_t *model) const = 0;
};

class iv_model_info_client : public ivmodelinfo
{
public:
};