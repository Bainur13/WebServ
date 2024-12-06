#include "../../Includes/utils_treat.hpp"

Location	search_location(std::string &path, Server_conf &server_c)
{
	Location	location;
	bool		match;

	std::vector<Location> locations = server_c.get_locations();
	std::string locations_path;
	std::string root;
	std::string best_match;

	while (1)
	{
		match = false;
		for (size_t i = 0; i < locations.size(); i++)
		{
			locations_path = locations[i].get_path();
			if (path.find(locations_path) == 0)
			{
				if (locations_path.size() > best_match.size())
				{
					if (locations[i].get_root() == "")
					{
						location = locations[i];
						continue ;
					}
					std::cout << "location root: " << locations[i].get_root() << std::endl;
					root = locations[i].get_root();
					best_match = locations_path;
					location = locations[i];
				}
				match = true;
			}
		}
		if (!match)
			break ;
		if (location.get_alias() != "")
		{
			if (root == "")
				path = server_c.get_root() + location.get_alias();
			else
				path = root + location.get_alias();
		}
		else
			path.replace(path.find(best_match), best_match.size(), root);
		best_match.clear();
	}
	if (location.get_path() == "")
		path = server_c.get_root() + path;
	return (location);
}

bool	check_method_right(std::vector<std::string> methods,
		std::string amethod)
{
	for (size_t i = 0; i < methods.size(); i++)
	{
		if (methods[i] == amethod)
			return (true);
	}
	return (false);
}

std::string get_content_type(const std::string &path)
{
	size_t	dot_pos;

	std::map<std::string, std::string> type_map;
	type_map[".html"] = "text/html";
	type_map[".css"] = "text/css";
	type_map[".js"] = "text/javascript";
	type_map[".jpg"] = "image/jpeg";
	type_map[".jpeg"] = "image/jpeg";
	type_map[".png"] = "image/png";
	type_map[".gif"] = "image/gif";
	type_map[".json"] = "application/json";
 	dot_pos = path.rfind('.');
	if (dot_pos != std::string::npos)
	{
		std::string extension = path.substr(dot_pos);
		if (type_map.find(extension) != type_map.end())
		{
			return (type_map[extension]);
		}
	}
	return ("application/octet-stream");
}
