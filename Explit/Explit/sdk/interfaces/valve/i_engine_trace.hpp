#pragma once
#include "../../sdk.hpp"

#pragma region masks

#define   dispsurf_flag_surface           (1<<0)
#define   dispsurf_flag_walkable          (1<<1)
#define   dispsurf_flag_buildable         (1<<2)
#define   dispsurf_flag_surfprop1         (1<<3)
#define   dispsurf_flag_surfprop2         (1<<4)

#define   contents_empty                0

#define   contents_solid                0x1       
#define   contents_window               0x2
#define   contents_aux                  0x4
#define   contents_grate                0x8
#define   contents_slime                0x10
#define   contents_water                0x20
#define   contents_blocklos             0x40 
#define   contents_opaque               0x80 
#define   last_visible_contents         contents_opaque

#define   all_visible_contents            (last_visible_contents | (last_visible_contents-1))

#define   contents_testfogvolume        0x100
#define   contents_unused               0x200     
#define   contents_blocklight           0x400
#define   contents_team1                0x800 
#define   contents_team2                0x1000 
#define   contents_ignore_nodraw_opaque 0x2000
#define   contents_moveable             0x4000
#define   contents_areaportal           0x8000
#define   contents_playerclip           0x10000
#define   contents_monsterclip          0x20000
#define   contents_current_0            0x40000
#define   contents_current_90           0x80000
#define   contents_current_180          0x100000
#define   contents_current_270          0x200000
#define   contents_current_up           0x400000
#define   contents_current_down         0x800000

#define   contents_origin               0x1000000 

#define   contents_monster              0x2000000 
#define   contents_debris               0x4000000
#define   contents_detail               0x8000000 
#define   contents_translucent          0x10000000
#define   contents_ladder               0x20000000
#define   contents_hitbox               0x40000000

#define   surf_light                    0x0001 
#define   surf_sky2d                    0x0002 
#define   surf_sky                      0x0004 
#define   surf_warp                     0x0008 
#define   surf_trans                    0x0010
#define   surf_noportal                 0x0020 
#define   surf_trigger                  0x0040 
#define   surf_nodraw                   0x0080 

#define   surf_hint                     0x0100 

#define   surf_skip                     0x0200   
#define   surf_nolight                  0x0400   
#define   surf_bumplight                0x0800   
#define   surf_noshadows                0x1000   
#define   surf_nodecals                 0x2000   
#define   surf_nopaint                  surf_nodecals
#define   surf_nochop                   0x4000   
#define   surf_hitbox                   0x8000   

// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define   mask_all                      (0xffffffff)
#define   mask_solid                    (contents_solid|contents_moveable|contents_window|contents_monster|contents_grate)
#define   mask_playersolid              (contents_solid|contents_moveable|contents_playerclip|contents_window|contents_monster|contents_grate)
#define   mask_npcsolid                 (contents_solid|contents_moveable|contents_monsterclip|contents_window|contents_monster|contents_grate)
#define   mask_npcfluid                 (contents_solid|contents_moveable|contents_monsterclip|contents_window|contents_monster)
#define   mask_water                    (contents_water|contents_moveable|contents_slime)
#define   mask_opaque                   (contents_solid|contents_moveable|contents_opaque)
#define   mask_opaque_and_npcs          (mask_opaque|contents_monster)
#define   mask_blocklos                 (contents_solid|contents_moveable|contents_blocklos)
#define   mask_blocklos_and_npcs        (mask_blocklos|contents_monster)
#define   mask_visible                  (mask_opaque|contents_ignore_nodraw_opaque)
#define   mask_visible_and_npcs         (mask_opaque_and_npcs|contents_ignore_nodraw_opaque)
#define   mask_shot                     (contents_solid|contents_moveable|contents_monster|contents_window|contents_debris|contents_hitbox)
#define   mask_shot_brushonly           (contents_solid|contents_moveable|contents_window|contents_debris)
#define   mask_shot_hull                (contents_solid|contents_moveable|contents_monster|contents_window|contents_debris|contents_grate)
#define   mask_shot_portal              (contents_solid|contents_moveable|contents_window|contents_monster)
#define   mask_solid_brushonly          (contents_solid|contents_moveable|contents_window|contents_grate)
#define   mask_playersolid_brushonly    (contents_solid|contents_moveable|contents_window|contents_playerclip|contents_grate)
#define   mask_npcsolid_brushonly       (contents_solid|contents_moveable|contents_window|contents_monsterclip|contents_grate)
#define   mask_npcworldstatic           (contents_solid|contents_window|contents_monsterclip|contents_grate)
#define   mask_npcworldstatic_fluid     (contents_solid|contents_window|contents_monsterclip)
#define   mask_splitareaportal          (contents_water|contents_slime)
#define   mask_current                  (contents_current_0|contents_current_90|contents_current_180|contents_current_270|contents_current_up|contents_current_down)
#define   mask_deadsolid                (contents_solid|contents_playerclip|contents_window|contents_grate)
#pragma endregion

class i_handle_entity;
struct ray_t;
class c_game_trace;
typedef c_game_trace trace_t;
class i_collideable;
class i_trace_list_data;
class c_phys_collide;
struct c_plane_t;
struct virtual_mesh_list_t;

enum class trace_type
{
	trace_everything = 0,
	trace_world_only,
	trace_entities_only,
	trace_everything_filter_props,
};

class i_trace_filter
{
public:
	virtual bool shouldhitentity(i_handle_entity *pentity, int contentsmask) = 0;
	virtual trace_type gettracetype() const = 0;
};


//-----------------------------------------------------------------------------
// classes are expected to inherit these + implement the shouldhitentity method
//-----------------------------------------------------------------------------

// this is the one most normal traces will inherit from
class c_trace_filter : public i_trace_filter
{
public:
	bool shouldhitentity(i_handle_entity* pentityhandle, int /*contentsmask*/)
	{
		client_class* pentcc = ((i_client_entity*)pentityhandle)->get_client_class();
		if (pentcc && strcmp(ccignore, ""))
		{
			if (pentcc->pnetwork_name == ccignore)
				return false;
		}

		return !(pentityhandle == pskip);
	}

	virtual trace_type gettracetype() const
	{
		return trace_type::trace_everything;
	}

	inline void setignoreclass(char* Class)
	{
		ccignore = Class;
	}

	void* pskip;
	char* ccignore = "";
};

class c_trace_filter_skip_entity : public i_trace_filter
{
public:
	c_trace_filter_skip_entity(i_handle_entity* pentityhandle)
	{
		pskip = pentityhandle;
	}

	bool shouldhitentity(i_handle_entity* pentityhandle, int /*contentsmask*/)
	{
		return !(pentityhandle == pskip);
	}
	virtual trace_type gettracetype() const
	{
		return trace_type::trace_everything;
	}
	void* pskip;
};

class c_trace_filter_entities_only : public i_trace_filter
{
public:
	bool shouldhitentity(i_handle_entity* pentityhandle, int /*contentsmask*/)
	{
		return true;
	}
	virtual trace_type gettracetype() const
	{
		return trace_type::trace_entities_only;
	}
};


//-----------------------------------------------------------------------------
// classes need not inherit from these
//-----------------------------------------------------------------------------
class c_trace_filter_world_only : public i_trace_filter
{
public:
	bool shouldhitentity(i_handle_entity* /*pserverentity*/, int /*contentsmask*/)
	{
		return false;
	}
	virtual trace_type gettracetype() const
	{
		return trace_type::trace_world_only;
	}
};

class ctracefilterworldandpropsonly : public i_trace_filter
{
public:
	bool shouldhitentity(i_handle_entity* /*pserverentity*/, int /*contentsmask*/)
	{
		return false;
	}
	virtual trace_type gettracetype() const
	{
		return trace_type::trace_everything;
	}
};

class c_trace_filter_players_only_skip_one : public i_trace_filter
{
public:
	c_trace_filter_players_only_skip_one(i_client_entity* ent)
	{
		pent = ent;
	}
	bool shouldhitentity(i_handle_entity* pentityhandle, int /*contentsmask*/)
	{
		return pentityhandle != pent && ((i_client_entity*)pentityhandle)->get_client_class()->class_id == class_id::ccsplayer;
	}
	virtual trace_type gettracetype() const
	{
		return trace_type::trace_entities_only;
	}

private:
	i_client_entity* pent;
};

class c_trace_filter_skip_two_entities : public i_trace_filter
{
public:
	c_trace_filter_skip_two_entities(i_client_entity* ent1, i_client_entity* ent2)
	{
		pent1 = ent1;
		pent2 = ent2;
	}
	bool shouldhitentity(i_handle_entity* pentityhandle, int /*contentsmask*/)
	{
		return !(pentityhandle == pent1 || pentityhandle == pent2);
	}
	virtual trace_type gettracetype() const
	{
		return trace_type::trace_everything;
	}

private:
	i_client_entity* pent1;
	i_client_entity* pent2;
};

class c_trace_filter_hit_all : public c_trace_filter
{
public:
	virtual bool shouldhitentity(i_handle_entity* /*pserverentity*/, int /*contentsmask*/)
	{
		return true;
	}
};


enum class debug_trace_counter_behavior_t
{
	ktrace_counter_set = 0,
	ktrace_counter_inc,
};

//-----------------------------------------------------------------------------
// enumeration interface for enumeratelinkentities
//-----------------------------------------------------------------------------
class i_entity_enumerator
{
public:
	// this gets called with each handle
	virtual bool enumentity(i_handle_entity *phandleentity) = 0;
};


struct brush_side_info_t
{
	Vector4D plane;               // the plane of the brush side
	unsigned short bevel;    // bevel plane?
	unsigned short thin;     // thin?
};

class c_phys_collide;

struct v_collide_t
{
	unsigned short solidcount : 15;
	unsigned short ispacked : 1;
	unsigned short descsize;
	// vphysicssolids
	c_phys_collide   **solids;
	char           *pkeyvalues;
	void           *puserdata;
};

struct c_model_t
{
	Vector         mins, maxs;
	Vector         origin;        // for sounds or lights
	int            headnode;
	v_collide_t     vcollisiondata;
};

struct c_surface_t
{
	const char     *name;
	short          surfaceprops;
	unsigned short flags;         // bugbug: these are declared per surface, not per material, but this database is per-material now
};

//-----------------------------------------------------------------------------
// a ray...
//-----------------------------------------------------------------------------
struct ray_t
{
	VectorAligned  m_start;  // starting point, centered within the extents
	VectorAligned  m_delta;  // direction + length of the ray
	VectorAligned  m_startoffset; // add this to m_start to get the actual ray start
	VectorAligned  m_extents;     // describes an axis aligned box extruded along a ray
	const matrix3x4_t *m_pworldaxistransform;
	bool m_isray;  // are the extents zero?
	bool m_isswept;     // is delta != 0?

	ray_t() : m_pworldaxistransform(NULL) {}

	void init(Vector const& start, Vector const& end)
	{
		m_delta = end - start;

		m_isswept = (m_delta.LengthSqr() != 0);

		m_extents.Init();

		m_pworldaxistransform = NULL;
		m_isray = true;

		// offset m_start to be in the center of the box...
		m_startoffset.Init();
		m_start = start;
	}

	void init(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs)
	{
		m_delta = end - start;

		m_pworldaxistransform = NULL;
		m_isswept = (m_delta.LengthSqr() != 0);

		m_extents = maxs - mins;
		m_extents *= 0.5f;
		m_isray = (m_extents.LengthSqr() < 1e-6);

		// offset m_start to be in the center of the box...
		m_startoffset = maxs + mins;
		m_startoffset *= 0.5f;
		m_start = start + m_startoffset;
		m_startoffset *= -1.0f;
	}
	Vector invdelta() const
	{
		Vector vecinvdelta;
		for (int iaxis = 0; iaxis < 3; ++iaxis) {
			if (m_delta[iaxis] != 0.0f) {
				vecinvdelta[iaxis] = 1.0f / m_delta[iaxis];
			}
			else {
				vecinvdelta[iaxis] = FLT_MAX;
			}
		}
		return vecinvdelta;
	}

private:
};

class c_base_trace
{
public:
	bool isdispsurface(void) { return ((dispflags & dispsurf_flag_surface) != 0); }
	bool isdispsurfacewalkable(void) { return ((dispflags & dispsurf_flag_walkable) != 0); }
	bool isdispsurfacebuildable(void) { return ((dispflags & dispsurf_flag_buildable) != 0); }
	bool isdispsurfaceprop1(void) { return ((dispflags & dispsurf_flag_surfprop1) != 0); }
	bool isdispsurfaceprop2(void) { return ((dispflags & dispsurf_flag_surfprop2) != 0); }

public:

	// these members are aligned!!
	Vector         startpos;            // start position
	Vector         endpos;              // final position
	c_plane_t       plane;               // surface normal at impact

	float          fraction;            // time completed, 1.0 = didn't hit anything

	int            contents;            // contents on other side of surface hit
	unsigned short dispflags;           // displacement flags for marking surfaces with data

	bool           allsolid;            // if true, plane is not valid
	bool           startsolid;          // if true, the initial point was in a solid area

	c_base_trace() {}

};

class c_game_trace : public c_base_trace
{
public:
	bool didhitworld() const;
	bool didhitnonworldentity() const;
	int getentityindex() const;
	bool didhit() const;
	bool isvisible() const;

public:

	float               fractionleftsolid;  // time we left a solid, only valid if we started in solid
	c_surface_t          surface;            // surface hit (impact surface)
	int                 hitgroup;           // 0 == generic, non-zero is specific body part
	short               physicsbone;        // physics bone hit by trace in studio
	unsigned short      worldsurfaceindex;  // index of the msurface2_t, if applicable
	i_client_entity*      hit_entity;
	int                 hitbox;                       // box hit by trace in studio

	c_game_trace() {}

private:
	// no copy constructors allowed
	c_game_trace(const c_game_trace& other) :
		fractionleftsolid(other.fractionleftsolid),
		surface(other.surface),
		hitgroup(other.hitgroup),
		physicsbone(other.physicsbone),
		worldsurfaceindex(other.worldsurfaceindex),
		hit_entity(other.hit_entity),
		hitbox(other.hitbox)
	{
		startpos = other.startpos;
		endpos = other.endpos;
		plane = other.plane;
		fraction = other.fraction;
		contents = other.contents;
		dispflags = other.dispflags;
		allsolid = other.allsolid;
		startsolid = other.startsolid;
	}
};

inline bool c_game_trace::didhit() const
{
	return fraction < 1 || allsolid || startsolid;
}

inline bool c_game_trace::isvisible() const
{
	return fraction > 0.97f;
}

class i_engine_trace
{
public:
	virtual int   get_point_contents(const Vector &vecabsposition, int contentsmask = mask_all, i_handle_entity** ppentity = nullptr) = 0;
	virtual int   get_point_contents_world_only(const Vector &vecabsposition, int contentsmask = mask_all) = 0;
	virtual int   get_point_contents_collideable(i_collideable *pcollide, const Vector &vecabsposition) = 0;
	virtual void  clip_ray_to_entity(const ray_t &ray, unsigned int fmask, i_handle_entity *pent, c_game_trace *ptrace) = 0;
	virtual void  clip_ray_to_collideable(const ray_t &ray, unsigned int fmask, i_collideable *pcollide, c_game_trace *ptrace) = 0;
	virtual void  trace_ray(const ray_t &ray, unsigned int fmask, i_trace_filter *ptracefilter, c_game_trace *ptrace) = 0;
};