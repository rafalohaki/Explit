#pragma once

#include "../../sdk.hpp"

typedef float quaternion[4];
typedef float radian_euler[3];

#define MAX_QPATH  260

#define BONE_CALCULATE_MASK             0x1F
#define BONE_PHYSICALLY_SIMULATED       0x01    // bone is physically simulated when physics are active
#define BONE_PHYSICS_PROCEDURAL         0x02    // procedural when physics is active
#define BONE_ALWAYS_PROCEDURAL          0x04    // bone is always procedurally animated
#define BONE_SCREEN_ALIGN_SPHERE        0x08    // bone aligns to the screen, not constrained in motion.
#define BONE_SCREEN_ALIGN_CYLINDER      0x10    // bone aligns to the screen, constrained by it's own axis.

#define BONE_USED_MASK                  0x0007FF00
#define BONE_USED_BY_ANYTHING           0x0007FF00
#define BONE_USED_BY_HITBOX             0x00000100    // bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT         0x00000200    // bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK        0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0        0x00000400    // bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1        0x00000800    
#define BONE_USED_BY_VERTEX_LOD2        0x00001000  
#define BONE_USED_BY_VERTEX_LOD3        0x00002000
#define BONE_USED_BY_VERTEX_LOD4        0x00004000
#define BONE_USED_BY_VERTEX_LOD5        0x00008000
#define BONE_USED_BY_VERTEX_LOD6        0x00010000
#define BONE_USED_BY_VERTEX_LOD7        0x00020000
#define BONE_USED_BY_BONE_MERGE         0x00040000    // bone is available for bone merge to occur against it

#define BONE_USED_BY_VERTEX_AT_LOD(lod) ( BONE_USED_BY_VERTEX_LOD0 << (lod) )
#define BONE_USED_BY_ANYTHING_AT_LOD(lod) ( ( BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK ) | BONE_USED_BY_VERTEX_AT_LOD(lod) )

#define MAX_NUM_LODS 8
#define MAXSTUDIOBONES		128		// total bones actually used

#define BONE_TYPE_MASK                  0x00F00000
#define BONE_FIXED_ALIGNMENT            0x00100000    // bone can't spin 360 degrees, all interpolation is normalized around a fixed orientation

#define BONE_HAS_SAVEFRAME_POS          0x00200000    // Vector48
#define BONE_HAS_SAVEFRAME_ROT64        0x00400000    // Quaternion64
#define BONE_HAS_SAVEFRAME_ROT32        0x00800000    // Quaternion32

#define Assert( _exp ) ((void)0)

#define HITGROUP_GENERIC 0
#define HITGROUP_HEAD 1
#define HITGROUP_CHEST 2
#define HITGROUP_STOMACH 3
#define HITGROUP_LEFTARM 4    
#define HITGROUP_RIGHTARM 5
#define HITGROUP_LEFTLEG 6
#define HITGROUP_RIGHTLEG 7
#define HITGROUP_GEAR 10

enum mod_type_t
{
	mod_bad = 0,
	mod_brush,
	mod_sprite,
	mod_studio
};

enum hitboxes
{
	hitbox_head,
	hitbox_neck,
	hitbox_pelvis,
	hitbox_stomach,
	hitbox_lower_chest,
	hitbox_chest,
	hitbox_upper_chest,
	hitbox_right_thigh,
	hitbox_left_thigh,
	hitbox_right_calf,
	hitbox_left_calf,
	hitbox_right_foot,
	hitbox_left_foot,
	hitbox_right_hand,
	hitbox_left_hand,
	hitbox_right_upper_arm,
	hitbox_right_forearm,
	hitbox_left_upper_arm,
	hitbox_left_forearm,
	hitbox_max
};

typedef unsigned short mdl_handle_t;

struct mstudio_bone_t
{
	int sznameindex;
	inline char *const pszname(void) const { return ((char *)this) + sznameindex; }
	int parent;
	int bonecontroller[6];

	Vector pos;
	quaternion quat;
	radian_euler rot;

	Vector posscale;
	Vector rotscale;

	matrix3x4_t posetobone;
	quaternion qalignment;
	int flags;
	int proctype;
	int procindex;
	mutable int physicsbone;
	inline void *pprocedure() const { if (procindex == 0) return NULL; else return  (void *)(((byte *)this) + procindex); };
	int surfacepropidx;
	inline char *const pszsurfaceprop(void) const { return ((char *)this) + surfacepropidx; }
	inline int getsurfaceprop(void) const { return surfaceproplookup; }

	int contents;
	int surfaceproplookup;
	int unused[7];
};


struct mstudio_bbox_t
{
	int         bone;
	int         group;
	Vector      bbmin;
	Vector      bbmax;
	int         szhitboxnameindex;
	int32_t     m_ipad01[3];
	float       m_flradius;
	int32_t     m_ipad02[4];

	char *gethitboxname()
	{
		if (szhitboxnameindex == 0)
			return "";

		return ((char*)this) + szhitboxnameindex;
	}
};

struct mstudio_hitbox_set_t
{
	int    sznameindex;
	int    numhitboxes;
	int    hitboxindex;

	inline char *const pszname(void) const
	{
		return ((char*)this) + sznameindex;
	}

	inline mstudio_bbox_t *phitbox(int i) const
	{
		if (i > numhitboxes) return nullptr;
		return (mstudio_bbox_t*)((uint8_t*)this + hitboxindex) + i;
	}
};

struct model_t
{
	char name[255];
};

class studio_hdr_t
{
public:

	__int32 id;                     //0x0000 
	__int32 version;                //0x0004 
	long    checksum;               //0x0008 
	char    szname[64];             //0x000c 
	__int32 length;                 //0x004c 
	Vector  veceyepos;              //0x0050 
	Vector  vecillumpos;            //0x005c 
	Vector  vechullmin;             //0x0068 
	Vector  vechullmax;             //0x0074 
	Vector  vecbbmin;               //0x0080 
	Vector  vecbbmax;               //0x008c 
	__int32 flags;                  //0x0098 
	__int32 numbones;               //0x009c 
	__int32 boneindex;              //0x00a0 
	__int32 numbonecontrollers;     //0x00a4 
	__int32 bonecontrollerindex;    //0x00a8 
	__int32 numhitboxsets;          //0x00ac 
	__int32 hitboxsetindex;         //0x00b0 
	__int32 numlocalanim;           //0x00b4 
	__int32 localanimindex;         //0x00b8 
	__int32 numlocalseq;            //0x00bc 
	__int32 localseqindex;          //0x00c0 
	__int32 activitylistversion;    //0x00c4 
	__int32 eventsindexed;          //0x00c8 
	__int32 numtextures;            //0x00cc 
	__int32 textureindex;           //0x00d0

	inline const char *pszname(void) const { return szname; }

	mstudio_hitbox_set_t* phitboxset(int i)
	{
		if (i > numhitboxsets) return nullptr;
		return (mstudio_hitbox_set_t*)((uint8_t*)this + hitboxsetindex) + i;
	}
	mstudio_bone_t* pbone(int i)
	{
		if (i > numbones) return nullptr;
		return (mstudio_bone_t*)((uint8_t*)this + boneindex) + i;
	}

};//size=0x00d4