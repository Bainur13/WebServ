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
			_servers_conf.push_back(parse_server(file));
		else
			error_exit("Error: invalid line in file");
	}
	check_servers();
	file.close();
}

Server_conf Conf::parse_server(std::ifstream &file)
{
	Server_conf server;

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
			server.set_server_conf_name(line_s);
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
	if (!unique_symbol(line_s, "}"))
		error_exit("Error: invalid server");
	return (server);
}

Location Conf::parse_location(std::ifstream &file, std::vector<std::string> line_path)
{
	Location location;
	std::string line;
	std::vector<std::string> line_s;

	location.set_path(line_path);
	while (std::getline(file, line))
	{
		line_s = split_line(line, " ");
		if (line_s.size() == 0)
			continue;
		if (line_s[0] == "root")
			location.set_root(line_s);
		if (line_s[0] == "index")
			location.set_index(line_s);
		if (line_s[0] == "error_page")
			location.set_error_page(line_s);
		if (line_s[0] == "redirect")
			location.set_redirect(line_s);
		if (line_s[0] == "method")
			location.set_method(line_s);
		if (line_s[0] == "auto_index")
			location.set_listing(line_s);
		if (unique_symbol(line_s, "}"))
			break;
	}
	return (location);
}

void Conf::check_servers()
{
	if (_servers_conf.size() == 0)
		error_exit("Error: no server");
	for (size_t i = 0; i < _servers_conf.size(); i++)
	{
		for (size_t j = i + 1; j < _servers_conf.size(); j++)
		{
			if (_servers_conf[i].get_host() == _servers_conf[j].get_host() && _servers_conf[i].get_port() == _servers_conf[j].get_port())
				error_exit("Error: duplicate server");
			if (_servers_conf[i].get_server_conf_name() == _servers_conf[j].get_server_conf_name())
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

std::vector<Server_conf> Conf::getServers() const
{
	return _servers_conf;
}

Conf::~Conf()
{
}
