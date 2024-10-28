/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_index.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:36:58 by bainur            #+#    #+#             */
/*   Updated: 2024/10/28 18:18:12 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/auto_index.hpp"

std::string soloslash(std::string path)
{
	for (size_t i = 0; i < path.size(); i++)
	{
		std::cout << path[i] << std::endl;
		if (path[i] == '/' && path[i + 1] == '/')
		{
			std::cout << "erase" << std::endl;
			path.erase(i, 1);
			i--;
		}
	}
	return (path);
}

bool	auto_index(std::string path, Location &location, Server_conf &server_c,
		Response &res)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(path.c_str());
	if (dir == NULL)
	{
		res.error_location("Error 404 : Not Found", 404, location, server_c);
		return (false);
	}
	if (location.get_auto_index_cgi_path() != "")
	{
		launch_auto_index_cgi(location, dir, res);
		closedir(dir);
		return (true);
	}
	path = soloslash(path);
	std::string body = "<html>\n<head>\n<title>Index of " + path
		+ "</title>\n</head>\n<body>\n<h1>Index of " + path + "</h1>\n<ul>\n";
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue ;
		std::cout << "entry->d_name" << path << entry->d_name << std::endl;
		struct stat buffer;
		std::string file_path = path + entry->d_name;
		if (stat(file_path.c_str(), &buffer) == 0)
		{
			if (S_ISDIR(buffer.st_mode))
				body += "<li><a href=\"./" + (std::string)entry->d_name + "/\">" + entry->d_name + "</a></li>\n";
			else if (S_ISREG(buffer.st_mode))
				body += "<li><a href=\"./" + (std::string)entry->d_name + "\">" + entry->d_name + "</a></li>\n";
		}
	}
	body += "</ul>\n</body>\n</html>";
	res.set_line("Version", "HTTP/1.1");
	res.set_line("Status", "200");
	res.set_line("Reason", "OK");
	res.set_header("Content-Type", "text/html");
	res.set_body(body);
	res.set_header("Content-Length", res.get_body_size());
	closedir(dir);
	return (true);
}
