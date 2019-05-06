#pragma once
#include "../../sdk.hpp"

class c_glow_manager {
public:
	struct glow_object_definition_t {
		glow_object_definition_t() { memset(this, 0, sizeof(*this)); }

		class c_base_entity* p_entity;    //0x0000
		union {
			Vector glow_color;           //0x0004
			struct {
				float   red;           //0x0004
				float   green;         //0x0008
				float   blue;          //0x000C
			};
		};
		float   alpha;                 //0x0010
		uint8_t pad_0014[4];               //0x0014
		float   m_flsomefloat;             //0x0018
		uint8_t pad_001C[4];               //0x001C
		float   m_flanotherfloat;          //0x0020
		bool    render_when_occluded;     //0x0024
		bool    render_when_unoccluded;   //0x0025
		bool    full_bloom_render;        //0x0026
		uint8_t pad_0027[5];               //0x0027
		int32_t glow_style;              //0x002C
		int32_t split_screen_slot;        //0x0030
		int32_t next_free_slot;           //0x0034

		bool is_unused() const { return next_free_slot != -2; }
	};

	glow_object_definition_t* glow_object_definitions;
	int		max_size;
	int		pad;
	int		size;
	glow_object_definition_t* glow_object_definitions2;
	int		current_objects;
};