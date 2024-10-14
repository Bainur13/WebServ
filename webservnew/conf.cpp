/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:25:48 by bainur            #+#    #+#             */
/*   Updated: 2024/10/14 19:20:44 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.hpp"

Conf::Conf()
{
}

Conf::Conf(const std::string &filename)
{
	std::ifstream file;
	std::string line;
	file.open(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file" << std::endl;
		exit(EXIT_FAILURE);
	}
	while (std::getline(file, line))
	{
		if (is_empty(line))
			continue;
		else if (is_server(line, file))
			_servers.push_back(parse_server(file));
		else
			error_exit("Error: invalid line in file");
	}
	check_servers();
	file.close();
}

Server Conf::parse_server(std::ifstream &file)
{
	Server server;

	std::string line;
	std::vector<std::string> line_s;
	while (std::getline(file, line))
	{
		line_s = split_line(line, " ");
		if (line_s.size() == 0)
			continue;
		if (unique_symbol(line_s, "}"))
			break;
		if (line_s[0] == "server_name")
			server.set_server_name(line_s);
		else if (line_s[0] == "root")
			server.set_root(line_s);
		else if (line_s[0] == "size_limit")
			server.set_sizelimit(line_s);
		else if (line_s[0] == "listen")
			server.set_listen(line_s);
		else if (line_s[0] == "error_page")
			server.set_error_page(line_s);
		else if (line_s[0] == "index")
			server.set_index(line_s);
		else if (line_s[0] == "method")
			server.set_method(line_s);
		else if (is_location(line, file))
			server.add_location(parse_location(file, line_s));
		else
			error_exit("Error: invalid line in server");
	}
	return (server);
}

Location Conf::parse_location(std::ifstream &file, std::vector<std::string> line_s)
{
	Location location;
	std::string line;
	std::vector<std::string> line_s;

	location.set_path(line_s);
	while (std::getline(file, line))
	{
		line_s = split_line(line, " ");
		if (line_s.size() == 0)
			continue;
		if (unique_symbol(line_s, "}"))
			break;
		
	}
	

}

void Conf::check_servers()
{
	if (_servers.size() == 0)
		error_exit("Error: no server");
	for (size_t i = 0; i < _servers.size(); i++)
	{
		for (size_t j = i + 1; j < _servers.size(); j++)
		{
			if (_servers[i].get_host() == _servers[j].get_host() && _servers[i].get_port() == _servers[j].get_port())
				error_exit("Error: duplicate server");
			if (_servers[i].get_server_name() == _servers[j].get_server_name())
				error_exit("Error: duplicate server name");
		}
	}
}

Conf::Conf(const Conf &copy)
{
	*this = copy;
}

Conf &Conf::operator=(const Conf &copy)
{
	if (this != &copy)
	{
	}
	return (*this);
}

Conf::~Conf()
{
}
