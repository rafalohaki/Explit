#pragma once

#include "../../math/VMatrix.hpp"

class i_panel;
class c_base_entity;

enum class clear_flags_t
{
	view_clear_color = 0x1,
	view_clear_depth = 0x2,
	view_clear_full_target = 0x4,
	view_no_draw = 0x8,
	view_clear_obey_stencil = 0x10,
	view_clear_stencil = 0x20,
};


enum class motion_blur_mode_t
{
	motion_blur_disable = 1,
	motion_blur_game = 2,
	motion_blur_sfm = 3
};

class c_view_setup
{
public:
	__int32   x;                  //0x0000 
	__int32   x_old;              //0x0004 
	__int32   y;                  //0x0008 
	__int32   y_old;              //0x000c 
	__int32   width;              //0x0010 
	__int32   width_old;          //0x0014 
	__int32   height;             //0x0018 
	__int32   height_old;         //0x001c 
	char      pad_0x0020[0x90];   //0x0020
	float     fov;                //0x00b0 
	float     viewmodel_fov;      //0x00b4 
	Vector    origin;             //0x00b8 
	Vector    angles;             //0x00c4 
	char      pad_0x00d0[0x7c];   //0x00d0

};//size=0x014c

class i_client_mode
{
public:
	virtual             ~i_client_mode() {}
	virtual int         client_mode_cs_normal(void *) = 0;
	virtual void        init() = 0;
	virtual void        init_viewport() = 0;
	virtual void        shutdown() = 0;
	virtual void        enable() = 0;
	virtual void        disable() = 0;
	virtual void        layout() = 0;
	virtual i_panel*    get_viewport() = 0;
	virtual void*       get_viewport_animation_controller() = 0;
	virtual void        process_input(bool bactive) = 0;
	virtual bool        should_draw_detail_objects() = 0;
	virtual bool        should_draw_entity(c_base_entity *pent) = 0;
	virtual bool        should_draw_local_player(c_base_entity *pplayer) = 0;
	virtual bool        should_draw_particles() = 0;
	virtual bool        should_draw_fog(void) = 0;
	virtual void        override_view(c_view_setup *psetup) = 0;
	virtual int         key_input(int down, int keynum, const char *pszcurrentbinding) = 0;
	virtual void        start_message_mode(int imessagemodetype) = 0;
	virtual i_panel*    get_message_panel() = 0;
	virtual void        override_mouse_input(float *x, float *y) = 0;
	virtual bool        creat_emove(float flinputsampletime, void* usercmd) = 0;
	virtual void        level_init(const char *newmap) = 0;
	virtual void        level_shutdown(void) = 0;
};