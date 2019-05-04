#include "config.hpp"

c_config g_config("C:\Explit\Configs\");

c_config::c_config(const std::string config_path)
{
	directory_path = config_path;
}

void c_config::save(const std::string config_name)
{
	const auto path = directory_path + config_name;
	
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

void c_config::load(const std::string config_name)
{
	const auto path = directory_path + config_name;
	
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