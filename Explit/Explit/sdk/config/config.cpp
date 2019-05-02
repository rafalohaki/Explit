#include "config.hpp"

c_config g_config("config.json");

c_config::c_config(const std::string config_path)
{
	char current_path[MAX_PATH] = "";
	GetModuleFileNameA(NULL, current_path, MAX_PATH);
	PathRemoveFileSpecA(current_path);
	PathAddBackslashA(current_path);
	path += config_path;
}

void c_config::save()
{
	std::ofstream out(path);

	if (!out.is_open())
	{
		return;
	}

	Json::Value save;

	save["Explit - Config"]["Misc"]["Watermark"] = settings.misc.watermark;

	out << save;

	out.close();
}

void c_config::load()
{
	std::ifstream in(path);

	if (!in.good())
	{
		save();
	}

	if (!in.is_open())
	{
		return;
	}

	Json::Value load;

	in >> load;

	settings.misc.watermark = load["Explit - Config"]["Misc"]["Watermark"].asBool();


	in.close();
}