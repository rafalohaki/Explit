#pragma once
#include "../sdk.hpp"

class c_config
{
public:
	c_config(const std::string directory_path);
	void load(const std::string config_name);
	void save(const std::string config_name);

	struct {
		bool unhook = false;
		struct {
			struct {
				bool esp = true;
				bool box = true;
				int box_type = 1;
				bool fill_box = false;
				bool outline_box = true;
				int health = 0;
				bool distance = false;
				bool name = false;
				bool weapon = false;
				bool visible = false;
				bool ammo = false;
				bool skeletons = false;
				bool snaplines = false;
				bool vulnerability = false;
				int armor = 0;
				bool money = false;
				bool enemies = true;
				bool team = false;
				bool weapons = false;
				bool local = false;
				bool nades = false;
				bool chickens = false;
			}esp;
			struct {
				bool chams = true;

			}chams;
			struct {
				bool glow = false;
				bool local = false;
				bool chickens = false;
				bool weapons = false;
				bool team = false;
				bool visible = false;
				bool enemy = false;
				int style = 0;
			}glow;
		}visuals;
		struct {
			bool watermark = true;
		}misc;
	} settings;
private:
	std::string directory_path;
};
extern c_config g_config;