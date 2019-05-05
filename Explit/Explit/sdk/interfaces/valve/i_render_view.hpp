#pragma once

#include "../../sdk.hpp"

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------
class c_view_setup;
class c_engine_sprite;
class i_client_entity;
class i_material;
struct model_t;
class i_client_renderable;
class i_texture;


//-----------------------------------------------------------------------------
// flags used by drawworldlists
//-----------------------------------------------------------------------------
enum
{
	drawworldlists_draw_strictlyabovewater = 0x001,
	drawworldlists_draw_strictlyunderwater = 0x002,
	drawworldlists_draw_intersectswater = 0x004,
	drawworldlists_draw_watersurface = 0x008,
	drawworldlists_draw_skybox = 0x010,
	drawworldlists_draw_clipskybox = 0x020,
	drawworldlists_draw_shadowdepth = 0x040,
	drawworldlists_draw_refraction = 0x080,
	drawworldlists_draw_reflection = 0x100,
	drawworldlists_draw_world_geometry = 0x200,
	drawworldlists_draw_decals_and_overlays = 0x400,
};

enum
{
	mat_sort_group_strictly_abovewater = 0,
	mat_sort_group_strictly_underwater,
	mat_sort_group_intersects_water_surface,
	mat_sort_group_watersurface,

	max_mat_sort_groups
};

//-----------------------------------------------------------------------------
// leaf index
//-----------------------------------------------------------------------------
typedef unsigned short leaf_index_t;
enum
{
	invalid_leaf_index = (leaf_index_t)~0
};

struct world_list_leaf_data_t
{
	leaf_index_t     leafindex;    // 16 bits
	int16_t         waterdata;
	uint16_t        firsttranslucentsurface;    // engine-internal list index
	uint16_t        translucentsurfacecount;    // count of translucent surfaces+disps
};

struct world_list_info_t
{
	int                     m_viewfogvolume;
	int                     m_leafcount;
	bool                    m_bhaswater;
	world_list_leaf_data_t*    m_pleafdatalist;
};

class i_world_render_list /*: public irefcounted*/
{
};

//-----------------------------------------------------------------------------
// describes the fog volume for a particular point
//-----------------------------------------------------------------------------
struct visible_fog_volume_info_t
{
	int            m_nvisiblefogvolume;
	int            m_nvisiblefogvolumeleaf;
	bool        m_beyeinfogvolume;
	float       m_fldistancetowater;
	float       m_flwaterheight;
	i_material*  m_pfogvolumematerial;
};

struct v_plane
{
	Vector        m_normal;
	vec_t        m_dist;
};
#define frustum_numplanes    6
typedef v_plane frustum[frustum_numplanes];
//-----------------------------------------------------------------------------
// vertex format for brush models
//-----------------------------------------------------------------------------
struct brush_vertex_t
{
	Vector        m_pos;
	Vector        m_normal;
	Vector        m_tangents;
	Vector        m_tangentt;
	vector2d    m_texcoord;
	vector2d    m_lightmapcoord;

private:
	brush_vertex_t(const brush_vertex_t& src);
};

//-----------------------------------------------------------------------------
// visibility data for area portal culling
//-----------------------------------------------------------------------------
struct vis_override_data_t
{
	Vector        m_vecvisorigin;                    // the point to to use as the viewpoint for area portal backface cull checks.
	float        m_fdisttoareaportaltolerance;    // the distance from an area portal before using the full screen as the viewable portion.
};


//-----------------------------------------------------------------------------
// interface for asking about the brush surfaces from the client dll
//-----------------------------------------------------------------------------

class i_brush_surface
{
public:
	// computes texture coordinates + lightmap coordinates given a world position
	virtual void computetexturecoordinate(Vector const& worldpos, vector2d& texcoord) = 0;
	virtual void computelightmapcoordinate(Vector const& worldpos, vector2d& lightmapcoord) = 0;

	// gets the vertex data for this surface
	virtual int  getvertexcount() const = 0;
	virtual void getvertexdata(brush_vertex_t* pverts) = 0;

	// gets at the material properties for this surface
	virtual i_material* getmaterial() = 0;
};


//-----------------------------------------------------------------------------
// interface for installing a new renderer for brush surfaces
//-----------------------------------------------------------------------------

class i_brush_renderer
{
public:
	// draws the surface; returns true if decals should be rendered on this surface
	virtual bool renderbrushmodelsurface(i_client_entity* pbaseentity, i_brush_surface* pbrushsurface) = 0;
};

#define max_vis_leaves    32
#define max_area_state_bytes        32
#define max_area_portal_state_bytes 24

class iv_render_view
{
	enum
	{
		view_setup_vis_ex_return_flags_uses_radial_vis = 0x00000001
	};
public:
	virtual void                drawbrushmodel(i_client_entity *baseentity, model_t *model, const Vector& origin, const QAngle& angles, bool sort) = 0;
	virtual void                drawidentitybrushmodel(i_world_render_list *plist, model_t *model) = 0;
	virtual void                touchlight(struct dlight_t *light) = 0;
	virtual void                draw3ddebugoverlays(void) = 0;
	virtual void                setblend(float blend) = 0;
	virtual float               getblend(void) = 0;
	virtual void                setcolormodulation(float const* blend) = 0;
	inline void                 setcolormodulation(float r, float g, float b)
	{
		float clr[3] = { r, g, b };
		setcolormodulation(clr);
	}
	virtual void                getcolormodulation(float* blend) = 0;
	virtual void                scenebegin(void) = 0;
	virtual void                sceneend(void) = 0;
	virtual void                getvisiblefogvolume(const Vector& eyepoint, visible_fog_volume_info_t *pinfo) = 0;
	virtual i_world_render_list*   createworldlist() = 0;
	virtual void                buildworldlists(i_world_render_list *plist, world_list_info_t* pinfo, int iforcefviewleaf, const vis_override_data_t* pvisdata = NULL, bool bshadowdepth = false, float *preflectionwaterheight = NULL) = 0;
	virtual void                drawworldlists(i_world_render_list *plist, unsigned long flags, float waterzadjust) = 0;
	virtual int                 getnumindicesforworldlists(i_world_render_list *plist, unsigned long nflags) = 0;
	virtual void                drawtopview(bool enable) = 0;
	virtual void                topviewbounds(vector2d const& mins, vector2d const& maxs) = 0;
	virtual void                drawlights(void) = 0;
	virtual void                drawmaskentities(void) = 0;
	virtual void                drawtranslucentsurfaces(i_world_render_list *plist, int *psortlist, int sortcount, unsigned long flags) = 0;
	virtual void                drawlinefile(void) = 0;
	virtual void                drawlightmaps(i_world_render_list *plist, int pageid) = 0;
	virtual void                viewsetupvis(bool novis, int numorigins, const Vector origin[]) = 0;
	virtual bool                areanyleavesvisible(int *leaflist, int nleaves) = 0;
	virtual    void             vguipaint(void) = 0;
	virtual void                viewdrawfade(uint8_t *color, i_material *pmaterial) = 0;
	virtual void                old_setprojectionmatrix(float fov, float znear, float zfar) = 0;
	virtual unsigned long       getlightatpoint(Vector& pos) = 0;
	virtual int                 getviewentity(void) = 0;
	virtual bool                isviewentity(int entindex) = 0;
	virtual float               getfieldofview(void) = 0;
	virtual unsigned char**     getareabits(void) = 0;
	virtual void                setfogvolumestate(int nvisiblefogvolume, bool buseheightfog) = 0;
	virtual void                installbrushsurfacerenderer(i_brush_renderer* pbrushrenderer) = 0;
	virtual void                drawbrushmodelshadow(i_client_renderable *prenderable) = 0;
	virtual    bool             leafcontainstranslucentsurfaces(i_world_render_list *plist, int sortindex, unsigned long flags) = 0;
	virtual bool                doesboxintersectwatervolume(const Vector &mins, const Vector &maxs, int leafwaterdataid) = 0;
	virtual void                setareastate(unsigned char chareabits[max_area_state_bytes], unsigned char chareaportalbits[max_area_portal_state_bytes]) = 0;
	virtual void                vgui_paint(int mode) = 0;
	virtual void                push3dview(const c_view_setup &view, int nflags, i_texture* prendertarget, frustum frustumplanes) = 0;
	virtual void                push2dview(const c_view_setup &view, int nflags, i_texture* prendertarget, frustum frustumplanes) = 0;
	virtual void                popview(frustum frustumplanes) = 0;
	virtual void                setmainview(const Vector &vecorigin, const QAngle &angles) = 0;
	virtual void                viewsetupvisex(bool novis, int numorigins, const Vector origin[], unsigned int &returnflags) = 0;
	virtual void                overrideviewfrustum(frustum custom) = 0;
	virtual void                drawbrushmodelshadowdepth(i_client_entity *baseentity, model_t *model, const Vector& origin, const QAngle& angles, bool bsort) = 0;
	virtual void                updatebrushmodellightmap(model_t *model, i_client_renderable *prenderable) = 0;
	virtual void                beginupdatelightmaps(void) = 0;
	virtual void                endupdatelightmaps(void) = 0;
	virtual void                old_setoffcenterprojectionmatrix(float fov, float znear, float zfar, float flaspectratio, float flbottom, float fltop, float flleft, float flright) = 0;
	virtual void                old_setprojectionmatrixortho(float left, float top, float right, float bottom, float znear, float zfar) = 0;
	virtual void                push3dview(const c_view_setup &view, int nflags, i_texture* prendertarget, frustum frustumplanes, i_texture* pdepthtexture) = 0;
	virtual void                getmatricesforview(const c_view_setup &view, VMatrix *pworldtoview, VMatrix *pviewtoprojection, VMatrix *pworldtoprojection, VMatrix *pworldtopixels) = 0;
};