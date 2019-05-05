#pragma once
#include "../../sdk.hpp"

class iv_model_render
{
public:
	virtual int                     drawmodel(int flags, i_client_renderable *prenderable, model_instance_handle_t instance, int entity_index, const model_t *model, Vector const& origin, QAngle const& angles, int skin, int body, int hitboxset, const matrix3x4_t *modeltoworld = NULL, const matrix3x4_t *plightingoffset = NULL) = 0;
	virtual void                    forcedmaterialoverride(i_material *newmaterial, override_type_t noverridetype = 0, int noverrides = 0) = 0;
	virtual bool                    isforcedmaterialoverride(void) = 0;
	virtual void                    setviewtarget(const c_studio_hdr *pstudiohdr, int nbodyindex, const Vector& target) = 0;
	virtual model_instance_handle_t   createinstance(i_client_renderable *prenderable, light_cache_handle_t *pcache = NULL) = 0;
	virtual void                    destroyinstance(model_instance_handle_t handle) = 0;
	virtual void                    setstaticlighting(model_instance_handle_t handle, light_cache_handle_t* phandle) = 0;
	virtual light_cache_handle_t      getstaticlighting(model_instance_handle_t handle) = 0;
	virtual bool                    changeinstance(model_instance_handle_t handle, i_client_renderable *prenderable) = 0;
	virtual void                    adddecal(model_instance_handle_t handle, ray_t const& ray, Vector const& decalup, int decalindex, int body, bool nopokethru, int maxlodtodecal) = 0;
	virtual void                    removealldecals(model_instance_handle_t handle) = 0;
	virtual bool                    modelhasdecals(model_instance_handle_t handle) = 0;
	virtual void                    removealldecalsfromallmodels() = 0;
	virtual matrix3x4_t*            drawmodelshadowsetup(i_client_renderable *prenderable, int body, int skin, draw_model_info_t *pinfo, matrix3x4_t *pcustombonetoworld = NULL) = 0;
	virtual void                    drawmodelshadow(i_client_renderable *prenderable, const draw_model_info_t &info, matrix3x4_t *pcustombonetoworld = NULL) = 0;
	virtual bool                    recomputestaticlighting(model_instance_handle_t handle) = 0;
	virtual void                    releaseallstaticpropcolordata(void) = 0;
	virtual void                    restoreallstaticpropcolordata(void) = 0;
	virtual int                     drawmodelex(model_render_info_t &pinfo) = 0;
	virtual int                     drawmodelexstaticprop(model_render_info_t &pinfo) = 0;
	virtual bool                    drawmodelsetup(model_render_info_t &pinfo, draw_model_state_t *pstate, matrix3x4_t **ppbonetoworldout) = 0;
	virtual void                    drawmodelexecute(i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& pinfo, matrix3x4_t* pcustombonetoworld = NULL) = 0;
	virtual void                    setuplighting(const Vector &veccenter) = 0;
	virtual int                     drawstaticproparrayfast(static_prop_render_info_t *pprops, int count, bool bshadowdepth) = 0;
	virtual void                    suppressenginelighting(bool bsuppress) = 0;
	virtual void                    setupcolormeshes(int ntotalverts) = 0;
	virtual void                    setuplightingex(const Vector &veccenter, model_instance_handle_t handle) = 0;
	virtual bool                    getbrightestshadowinglightsource(const Vector &veccenter, Vector& lightpos, Vector& lightbrightness, bool ballownontaggedlights) = 0;
	virtual void                    computelightingstate(int ncount, const lighting_query_t *pquery, material_lighting_state_t *pstate, i_texture **ppenvcubemaptexture) = 0;
	virtual void                    getmodeldecalhandles(studio_decal_handle_t *pdecals, int ndecalstride, int ncount, const model_instance_handle_t *phandles) = 0;
	virtual void                    computestaticlightingstate(int ncount, const static_lighting_query_t *pquery, material_lighting_state_t *pstate, material_lighting_state_t *pdecalstate, color_mesh_info_t **ppstaticlighting, i_texture **ppenvcubemaptexture, data_cache_handle_t *pcolormeshhandles) = 0;
	virtual void                    cleanupstaticlightingstate(int ncount, data_cache_handle_t *pcolormeshhandles) = 0;
};
