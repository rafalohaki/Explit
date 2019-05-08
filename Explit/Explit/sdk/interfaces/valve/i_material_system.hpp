#pragma once
#include "../../sdk.hpp"

#define DECLARE_POINTER_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
#define MAXSTUDIOSKINS		32

// These are given to FindMaterial to reference the texture groups that Show up on the 
#define TEXTURE_GROUP_LIGHTMAP						        "Lightmaps"
#define TEXTURE_GROUP_WORLD							          "World textures"
#define TEXTURE_GROUP_MODEL							          "Model textures"
#define TEXTURE_GROUP_VGUI							          "VGUI textures"
#define TEXTURE_GROUP_PARTICLE						        "Particle textures"
#define TEXTURE_GROUP_DECAL							          "Decal textures"
#define TEXTURE_GROUP_SKYBOX						          "SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				      "ClientEffect textures"
#define TEXTURE_GROUP_OTHER							          "Other textures"
#define TEXTURE_GROUP_PRECACHED						        "Precached"
#define TEXTURE_GROUP_CUBE_MAP						        "CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					      "RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					        "Unaccounted textures"
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		  "Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			    "Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			  "Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			  "Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					      "DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					        "ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					      "Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				      "Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			  "RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					      "Morph Targets"

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------
class i_material_proxy_factory;
class i_material_system_hardware_config;
struct material_system_config_t;
struct aspect_ratio_info_t;
struct materialsystemhwid_t;
class i_shader;

enum compiled_vtf_flags
{
	textureflags_pointsample = 0x00000001,
	textureflags_trilinear = 0x00000002,
	textureflags_clamps = 0x00000004,
	textureflags_clampt = 0x00000008,
	textureflags_anisotropic = 0x00000010,
	textureflags_hint_dxt5 = 0x00000020,
	textureflags_pwl_corrected = 0x00000040,
	textureflags_normal = 0x00000080,
	textureflags_nomip = 0x00000100,
	textureflags_nolod = 0x00000200,
	textureflags_all_mips = 0x00000400,
	textureflags_procedural = 0x00000800,
	textureflags_onebitalpha = 0x00001000,
	textureflags_eightbitalpha = 0x00002000,
	textureflags_envmap = 0x00004000,
	textureflags_rendertarget = 0x00008000,
	textureflags_depthrendertarget = 0x00010000,
	textureflags_nodebugoverride = 0x00020000,
	textureflags_singlecopy = 0x00040000,
	textureflags_pre_srgb = 0x00080000,
	textureflags_unused_00100000 = 0x00100000,
	textureflags_unused_00200000 = 0x00200000,
	textureflags_unused_00400000 = 0x00400000,
	textureflags_nodepthbuffer = 0x00800000,
	textureflags_unused_01000000 = 0x01000000,
	textureflags_clampu = 0x02000000,
	textureflags_vertextexture = 0x04000000,
	textureflags_ssbump = 0x08000000,
	textureflags_unused_10000000 = 0x10000000,
	textureflags_border = 0x20000000,
	textureflags_unused_40000000 = 0x40000000,
	textureflags_unused_80000000 = 0x80000000
};

enum standard_light_map_t
{
	material_system_lightmap_page_white = -1,
	material_system_lightmap_page_white_bump = -2,
	material_system_lightmap_page_user_defined = -3
};


struct material_system_sort_info_t
{
	i_material	*material;
	int			lightmappageid;
};

enum material_thread_mode_t
{
	material_single_threaded,
	material_queued_single_threaded,
	material_queued_threaded
};

enum material_context_type_t
{
	material_hardware_context,
	material_queued_context,
	material_NULL_context
};

enum
{
	material_adapter_name_length = 512
};

struct material_texture_info_t
{
	int iexcludeinformation;
};

struct application_performance_counters_info_t
{
	float msmain;
	float msmst;
	float msgpu;
	float msflip;
	float mstotal;
};

struct application_instant_counters_info_t
{
	uint32_t m_ncpuactivitymask;
	uint32_t m_ndeferredwordsallocated;
};
struct material_adapter_info_t
{
	char m_pdrivername[material_adapter_name_length];
	unsigned int m_vendorid;
	unsigned int m_deviceid;
	unsigned int m_subsysid;
	unsigned int m_revision;
	int m_ndxsupportlevel;			// this is the *preferred* dx support level
	int m_nmindxsupportlevel;
	int m_nmaxdxsupportlevel;
	unsigned int m_ndriverversionhigh;
	unsigned int m_ndriverversionlow;
};

struct material_video_mode_t
{
	int m_width;			// if width and height are 0 and you select 
	int m_height;			// windowed mode, it'll use the window size
	image_format m_format;	// use image_formats (ignored for windowed mode)
	int m_refreshrate;		// 0 == default (ignored for windowed mode)
};
enum hdr_type_t
{
	hdr_type_none,
	hdr_type_integer,
	hdr_type_float,
};

enum restore_change_flags_t
{
	material_restore_vertex_format_changed = 0x1,
	material_restore_release_managed_resources = 0x2,
};

enum render_target_size_mode_t
{
	rt_size_no_change = 0,
	rt_size_default = 1,
	rt_size_picmip = 2,
	rt_size_hdr = 3,
	rt_size_full_frame_buffer = 4,
	rt_size_offscreen = 5,
	rt_size_full_frame_buffer_rounded_up = 6
};

enum material_render_target_depth_t
{
	material_rt_depth_shared = 0x0,
	material_rt_depth_separate = 0x1,
	material_rt_depth_none = 0x2,
	material_rt_depth_only = 0x3,
};

typedef void(*materialbufferreleasefunc_t)(int nchangeflags);	// see restore_change_flags_t
typedef void(*materialbufferrestorefunc_t)(int nchangeflags);	// see restore_change_flags_t
typedef void(*modechangecallbackfunc_t)(void);
typedef void(*endframecleanupfunc_t)(void);
typedef bool(*endframepriortonextcontextfunc_t)(void);
typedef void(*onlevelshutdownfunc_t)(void *puserdata);

typedef unsigned short materialhandle_t;

class i_material_system : public i_app_system
{
public:

	virtual createinterfacefn               init(char const* pshaderapidll, i_material_proxy_factory *pmaterialproxyfactory, createinterfacefn filesystemfactory, createinterfacefn cvarfactory = NULL) = 0;
	virtual void                            setshaderapi(char const *pshaderapidll) = 0;
	virtual void                            setadapter(int nadapter, int nflags) = 0;
	virtual void                            modinit() = 0;
	virtual void                            modshutdown() = 0;
	virtual void                            setthreadmode(material_thread_mode_t mode, int nservicethread = -1) = 0;
	virtual material_thread_mode_t            getthreadmode() = 0;
	virtual void                            executequeued() = 0;
	virtual void                            ondebugevent(const char *pevent) = 0;
	virtual i_material_system_hardware_config*  gethardwareconfig(const char *pversion, int *returncode) = 0;
	virtual void                            __unknown() = 0;
	virtual bool                            updateconfig(bool bforceupdate) = 0; //20
	virtual bool                            overrideconfig(const material_system_config_t &config, bool bforceupdate) = 0;
	virtual const material_system_config_t&  getcurrentconfigforvideocard() const = 0;
	virtual bool                            getrecommendedconfigurationinfo(int ndxlevel, key_values * pkey_values) = 0;
	virtual int                             getdisplayadaptercount() const = 0;
	virtual int                             getcurrentadapter() const = 0;
	virtual void                            getdisplayadapterinfo(int adapter, material_adapter_info_t& info) const = 0;
	virtual int                             getmodecount(int adapter) const = 0;
	virtual void                            getmodeinfo(int adapter, int mode, material_video_mode_t& info) const = 0;
	virtual void                            addmodechangecallback(modechangecallbackfunc_t func) = 0;
	virtual void                            getdisplaymode(material_video_mode_t& mode) const = 0; //30
	virtual bool                            setmode(void* hwnd, const material_system_config_t &config) = 0;
	virtual bool                            supportsmsaamode(int nmsaamode) = 0;
	virtual const materialsystemhwid_t&     getvideocardidentifier(void) const = 0;
	virtual void                            spewdriverinfo() const = 0;
	virtual void                            getbackbufferdimensions(int &width, int &height) const = 0;
	virtual image_format                    getbackbufferformat() const = 0;
	virtual const aspect_ratio_info_t&        getaspectratioinfo() const = 0;
	virtual bool                            supportshdrmode(hdr_type_t nhdrmodede) = 0;
	virtual bool                            addview(void* hwnd) = 0;
	virtual void                            removeview(void* hwnd) = 0; //40
	virtual void                            setview(void* hwnd) = 0;
	virtual void                            beginframe(float frametime) = 0;
	virtual void                            endframe() = 0;
	virtual void                            flush(bool flushhardware = false) = 0;
	virtual unsigned int                    getcurrentframecount() = 0;
	virtual void                            swapbuffers() = 0;
	virtual void                            evictmanagedresources() = 0;
	virtual void                            releaseresources(void) = 0;
	virtual void                            reacquireresources(void) = 0;
	virtual void                            addreleasefunc(materialbufferreleasefunc_t func) = 0; //50
	virtual void                            removereleasefunc(materialbufferreleasefunc_t func) = 0;
	virtual void                            addrestorefunc(materialbufferrestorefunc_t func) = 0;
	virtual void                            removerestorefunc(materialbufferrestorefunc_t func) = 0;
	virtual void                            addendframecleanupfunc(endframecleanupfunc_t func) = 0;
	virtual void                            removeendframecleanupfunc(endframecleanupfunc_t func) = 0;
	virtual void                            onlevelshutdown() = 0;
	virtual bool                            addonlevelshutdownfunc(onlevelshutdownfunc_t func, void *puserdata) = 0;
	virtual bool                            removeonlevelshutdownfunc(onlevelshutdownfunc_t func, void *puserdata) = 0;
	virtual void                            onlevelloadingcomplete() = 0;
	virtual void                            resettemphwmemory(bool bexitinglevel = false) = 0; //60
	virtual void                            handledevicelost() = 0;
	virtual int                             shadercount() const = 0;
	virtual int                             getshaders(int nfirstshader, int nmaxcount, i_shader **ppshaderlist) const = 0;
	virtual int                             shaderflagcount() const = 0;
	virtual const char*                     shaderflagname(int nindex) const = 0;
	virtual void                            getshaderfallback(const char *pshadername, char *pfallbackshader, int nfallbacklength) = 0;
	virtual i_material_proxy_factory*          getmaterialproxyfactory() = 0;
	virtual void                            setmaterialproxyfactory(i_material_proxy_factory* pfactory) = 0;
	virtual void                            enableeditormaterials() = 0;
	virtual void                            enablegbuffers() = 0; //70
	virtual void                            setinstubmode(bool binstubmode) = 0;
	virtual void                            debugprintusedmaterials(const char *psearchsubstring, bool bverbose) = 0;
	virtual void                            debugprintusedtextures(void) = 0;
	virtual void                            togglesuppressmaterial(char const* pmaterialname) = 0;
	virtual void                            toggledebugmaterial(char const* pmaterialname) = 0;
	virtual bool                            usingfastclipping(void) = 0;
	virtual int                             stencilbufferbits(void) = 0; //number of bits per pixel in the stencil buffer
	virtual void                            uncacheallmaterials() = 0;
	virtual void                            uncacheunusedmaterials(bool brecomputestatesnapshots = false) = 0;
	virtual void                            cacheusedmaterials() = 0; //80
	virtual void                            reloadtextures() = 0;
	virtual void                            reloadmaterials(const char *psubstring = NULL) = 0;
	virtual i_material*                      creatematerial(const char *pmaterialname, key_values *pvmtkey_values) = 0;
	virtual i_material*                      findmaterial(char const* pmaterialname, const char *ptexturegroupname, bool complain = true, const char *pcomplainprefix = NULL) = 0;
	virtual void							unk0() = 0;
	virtual materialhandle_t                firstmaterial() const = 0;
	virtual materialhandle_t                nextmaterial(materialhandle_t h) const = 0;
	virtual materialhandle_t                invalidmaterial() const = 0;
	virtual i_material*                      getmaterial(materialhandle_t h) const = 0;
	virtual int                             getnummaterials() const = 0;
	virtual i_texture*                       findtexture(char const* ptexturename, const char *ptexturegroupname, bool complain = true) = 0;
	virtual bool                            istextureloaded(char const* ptexturename) const = 0;
	virtual i_texture*                       createproceduraltexture(const char	*ptexturename, const char *ptexturegroupname, int w, int h, image_format fmt, int nflags) = 0;
	virtual void                            beginrendertargetallocation() = 0;
	virtual void                            endrendertargetallocation() = 0; // simulate an alt-tab in here, which causes a release/restore of all resources
	virtual i_texture*                       createrendertargettexture(int w, int h, render_target_size_mode_t sizemode, image_format	format, material_render_target_depth_t depth = material_rt_depth_shared) = 0;
	virtual i_texture*                       createnamedrendertargettextureex(const char *prtname, int w, int h, render_target_size_mode_t sizemode, image_format format, material_render_target_depth_t depth = material_rt_depth_shared, unsigned int textureflags = textureflags_clamps | textureflags_clampt, unsigned int rendertargetflags = 0) = 0;
	virtual i_texture*                       createnamedrendertargettexture(const char *prtname, int w, int h, render_target_size_mode_t sizemode, image_format format, material_render_target_depth_t depth = material_rt_depth_shared, bool bclamptexcoords = true, bool bautomipmap = false) = 0;
	virtual i_texture*                       createnamedrendertargettextureex2(const char *prtname, int w, int h, render_target_size_mode_t sizemode, image_format format, material_render_target_depth_t depth = material_rt_depth_shared, unsigned int textureflags = textureflags_clamps | textureflags_clampt, unsigned int rendertargetflags = 0) = 0;

};