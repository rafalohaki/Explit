#pragma once
#include "../../sdk.hpp"
enum preview_image_retval_t
{
	material_preview_image_bad = 0,
	material_preview_image_ok,
	material_no_preview_image,
};

enum material_var_flags_t
{
	material_var_debug = (1 << 0),
	material_var_no_debug_override = (1 << 1),
	material_var_no_draw = (1 << 2),
	material_var_use_in_fillrate_mode = (1 << 3),
	material_var_vertexcolor = (1 << 4),
	material_var_vertexalpha = (1 << 5),
	material_var_selfillum = (1 << 6),
	material_var_additive = (1 << 7),
	material_var_alphatest = (1 << 8),
	//material_var_unused = (1 << 9),
	material_var_znearer = (1 << 10),
	material_var_model = (1 << 11),
	material_var_flat = (1 << 12),
	material_var_nocull = (1 << 13),
	material_var_nofog = (1 << 14),
	material_var_ignorez = (1 << 15),
	material_var_decal = (1 << 16),
	material_var_envmapsphere = (1 << 17), // obsolete
	material_var_unused = (1 << 18), // unused
	material_var_envmapcameraspace = (1 << 19), // obsolete
	material_var_basealphaenvmapmask = (1 << 20),
	material_var_translucent = (1 << 21),
	material_var_normalmapalphaenvmapmask = (1 << 22),
	material_var_needs_software_skinning = (1 << 23), // obsolete
	material_var_opaquetexture = (1 << 24),
	material_var_envmapmode = (1 << 25), // obsolete
	material_var_suppress_decals = (1 << 26),
	material_var_halflambert = (1 << 27),
	material_var_wireframe = (1 << 28),
	material_var_allowalphatocoverage = (1 << 29),
	material_var_alpha_modified_by_proxy = (1 << 30),
	material_var_vertexfog = (1 << 31),
};

typedef unsigned short model_instance_handle_t;
typedef void* light_cache_handle_t;
typedef void* studio_decal_handle_t;
typedef int override_type_t;
typedef int image_format;
typedef int vertex_format_t;
typedef int material_property_types_t;

class i_client_renderable;
class i_material;
class c_studio_hdr;
class i_mat_render_context;
class data_cache_handle_t;
class i_texture;
class i_material_var;
class key_values;
struct model_t;
struct mstudio_anim_desc_t;
struct mstudio_seq_desc_t;
struct ray_t;
struct draw_model_info_t;
struct studio_hw_data_t;
struct material_lighting_state_t;
struct color_mesh_info_t;

struct draw_model_state_t
{
	studio_hdr_t*            m_pstudiohdr;
	studio_hw_data_t*         m_pstudiohwdata;
	i_client_renderable*      m_prenderable;
	const matrix3x4_t*      m_pmodeltoworld;
	studio_decal_handle_t     m_decals;
	int                     m_drawflags;
	int                     m_lod;
};

struct static_prop_render_info_t
{
	const matrix3x4_t*      pmodeltoworld;
	const model_t*          pmodel;
	i_client_renderable*      prenderable;
	Vector*                 plightingorigin;
	short                   skin;
	model_instance_handle_t   instance;
};

struct model_render_info_t
{
	Vector                  origin;
	QAngle                  angles;
	char					pad[0x4];
	i_client_renderable*      prenderable;
	const model_t*          pmodel;
	const matrix3x4_t*      pmodeltoworld;
	const matrix3x4_t*      plightingoffset;
	const Vector*           plightingorigin;
	int                     flags;
	int                     entity_index;
	int                     skin;
	int                     body;
	int                     hitboxset;
	model_instance_handle_t   instance;

	model_render_info_t()
	{
		pmodeltoworld = NULL;
		plightingoffset = NULL;
		plightingorigin = NULL;
	}
};

struct lighting_query_t
{
	Vector                  m_lightingorigin;
	model_instance_handle_t   m_instancehandle;
	bool                    m_bambientboost;
};

struct static_lighting_query_t : public lighting_query_t
{
	i_client_renderable*        m_prenderable;
};

class i_material
{
public:
	virtual const char*             getname() const = 0;
	virtual const char*             gettexturegroupname() const = 0;
	virtual preview_image_retval_t    getpreviewimageproperties(int *width, int *height, image_format *image_format, bool* istranslucent) const = 0;
	virtual preview_image_retval_t    getpreviewimage(unsigned char *data, int width, int height, image_format image_format) const = 0;
	virtual int                     getmappingwidth() = 0;
	virtual int                     getmappingheight() = 0;
	virtual int                     getnumanimationframes() = 0;
	virtual bool                    inmaterialpage(void) = 0;
	virtual    void                 getmaterialoffset(float *poffset) = 0;
	virtual void                    getmaterialscale(float *pscale) = 0;
	virtual i_material*              getmaterialpage(void) = 0;
	virtual i_material_var*           findvar(const char *varname, bool *found, bool complain = true) = 0;
	virtual void                    incrementreferencecount(void) = 0;
	virtual void                    decrementreferencecount(void) = 0;
	inline void                     addref() { incrementreferencecount(); }
	inline void                     release() { decrementreferencecount(); }
	virtual int                     getenumerationid(void) const = 0;
	virtual void                    getlowrescolorsample(float s, float t, float *color) const = 0;
	virtual void                    recomputestatesnapshots() = 0;
	virtual bool                    istranslucent() = 0;
	virtual bool                    isalphatested() = 0;
	virtual bool                    isvertexlit() = 0;
	virtual vertex_format_t          getvertexformat() const = 0;
	virtual bool                    hasproxy(void) const = 0;
	virtual bool                    usesenvcubemap(void) = 0;
	virtual bool                    needstangentspace(void) = 0;
	virtual bool                    needspoweroftwoframebuffertexture(bool bcheckspecifictothisframe = true) = 0;
	virtual bool                    needsfullframebuffertexture(bool bcheckspecifictothisframe = true) = 0;
	virtual bool                    needssoftwareskinning(void) = 0;
	virtual void                    alphamodulate(float alpha) = 0;
	virtual void                    colormodulate(float r, float g, float b) = 0;
	virtual void                    setmaterialvarflag(material_var_flags_t flag, bool on) = 0;
	virtual bool                    getmaterialvarflag(material_var_flags_t flag) const = 0;
	virtual void                    getreflectivity(Vector& reflect) = 0;
	virtual bool                    getpropertyflag(material_property_types_t type) = 0;
	virtual bool                    istwosided() = 0;
	virtual void                    setshader(const char *pshadername) = 0;
	virtual int                     getnumpasses(void) = 0;
	virtual int                     gettexturememorybytes(void) = 0;
	virtual void                    refresh() = 0;
	virtual bool                    needslightmapblendalpha(void) = 0;
	virtual bool                    needssoftwarelighting(void) = 0;
	virtual int                     shaderparamcount() const = 0;
	virtual i_material_var**          getshaderparams(void) = 0;
	virtual bool                    iserrormaterial() const = 0;
	virtual void                    unused() = 0;
	virtual float                   getalphamodulation() = 0;
	virtual void                    getcolormodulation(float *r, float *g, float *b) = 0;
	virtual bool                    istranslucentundermodulation(float falphamodulation = 1.0f) const = 0;
	virtual i_material_var*           findvarfast(char const *pvarname, unsigned int *ptoken) = 0;
	virtual void                    setshaderandparams(key_values *pkeyvalues) = 0;
	virtual const char*             getshadername() const = 0;
	virtual void                    deleteifunreferenced() = 0;
	virtual bool                    isspritecard() = 0;
	virtual void                    callbindproxy(void *proxydata) = 0;
	virtual void                    refreshpreservingmaterialvars() = 0;
	virtual bool                    wasreloadedfromwhitelist() = 0;
	virtual bool                    settempexcluded(bool bset, int nexcludeddimensionlimit) = 0;
	virtual int                     getreferencecount() const = 0;
};