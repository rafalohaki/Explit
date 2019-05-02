#pragma once
#include "../sdk.hpp"

class c_config
{
public:
	c_config(const std::string config_path);
	void load();
	void save();

	struct {
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
				bool glow = true;
			}glow;
		}visuals;
		struct {
			bool watermark = true;
		}misc;
	} settings;
private:
	std::string path;
};
extern c_config g_config;