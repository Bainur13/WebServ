/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:25:57 by bainur            #+#    #+#             */
/*   Updated: 2024/10/16 18:05:36 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Location	search_location(std::string &path, Server_conf server_c)
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
			if (locations[i].get_root() == "")
				continue ;
			if (path.find(locations_path) == 0)
			{
				if (locations_path.size() > best_match.size())
				{
					root = locations[i].get_root();
					best_match = locations_path;
					location = locations[i];
				}
				match = true;
			}
		}
		if (!match)
			break ;
		path.replace(path.find(best_match), best_match.size(), root);
		best_match.clear();
	}
	if (path.find(server_c.get_root()) != 0)
		path = server_c.get_root() + path;
	return (location);
}

bool	check_method_location(std::vector<std::string> methods,
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

bool	get_request(Request req, Server_conf server_c, Response &res)
{
	Location	location;
	int			fd;

	std::string path;
	path = req.get_request_line("Path");
	location = search_location(path, server_c);
	if (location.get_path() != "")
	{
		if (!check_method_location(location.get_method(), "GET"))
		{
			res.error_basic("Error 405 : Method Not Allowed", 405, server_c);
			return (false);
		}
		if (path.find_last_of("/") == path.size() - 1)
		{
			if (location.get_index() != "")
			{
				fd = open(path.c_str(), O_RDONLY);
				if (fd < 0)
				{
					res.error_basic("Error 404 : Not Found", 404, server_c);
					return (false);
				}
				res.set_body(read_fd_to_end(fd));
				close(fd);
			}
			// else if (location.get_autoindex())
			// {
			// 		res.set_body(autoindex(path));
			// }
			else
			{
				res.error_basic("Error 403 : Forbidden", 403, server_c);
				return (false);
			}
		}
		else
		{
			fd = open(path.c_str(), O_RDONLY);
			if (fd < 0)
			{
				res.error_basic("Error 404 : Not Found", 404, server_c);
				return (false);
			}
			res.set_body(read_fd_to_end(fd));
			close(fd);
		}
	}
	else
	{
		if (!check_method_location(server_c.get_method(), "GET"))
		{
			res.error_basic("Error 405 : Method Not Allowed", 405, server_c);
			return (false);
		}
		if (path.find_last_of("/") == path.size() - 1)
		{
			if (server_c.get_index() != "")
			{
				fd = open(path.c_str(), O_RDONLY);
				if (fd < 0)
				{
					res.error_basic("Error 404 : Not Found", 404, server_c);
					return (false);
				}
				res.set_body(read_fd_to_end(fd));
				close(fd);
			}
			else
			{
				res.error_basic("Error 403 : Forbidden", 403, server_c);
				return (false);
			}
		}
		else
		{
			fd = open(path.c_str(), O_RDONLY);
			if (fd < 0)
			{
				res.error_basic("Error 404 : Not Found", 404, server_c);
				return (false);
			}
			res.set_body(read_fd_to_end(fd));
			close(fd);
		}
	}
	if (res.get_body_size() == "0")
	{
		res.error_basic("Error 404 : Not Found", 404, server_c);
		return (false);
	}
	res.set_line("Version", req.get_request_line("Version"));
	res.set_line("Status", "200");
	res.set_line("Reason", "OK");
	res.set_header("Content-Type", get_content_type(path));
	res.set_header("Content-Length", res.get_body_size());
	return (true);
}

Response	treat_request(Request req, Server_conf server_c)
{
	Response	res;

	std::cout << "treating request" << std::endl;
	if (req.get_request_line("Method") == "GET")
	{
		get_request(req, server_c, res);
	}
	return (res);
}

void	handle_client(int client_fd, Server_conf &server_c)
{
	Response	res;
	Request		req;

	std::string request;
	std::cout << "Client connected" << std::endl;
	request = read_fd_to_end(client_fd);
	if (request.empty())
	{
		close(client_fd);
		return ;
	}
	req.print_request();
	if (req.get_request_body().size() > (uint)server_c.get_sizelimit())
		res.error_basic("Error 413 : Payload Too Large", 413, server_c);
	if (req.get_error() != "")
	{
		std::cerr << req.get_error() << std::endl;
		res.error_basic(req.get_error(), 400, server_c);
	}
	else
	{
		res = treat_request(req, server_c);
	}
	std::string response = res.final_response();
	std::cout << "Response sent:" << std::endl;
	std::cout << response << std::endl;
	if (send(client_fd, response.c_str(), response.size(), 0) == -1)
	{
		std::cerr << strerror(errno) << std::endl;
		close(client_fd);
		return ;
	}
	close(client_fd);
}

void	init_servers(Conf &conf)
{
	int					epoll_fd;
	int					ndfs;
	bool				server_status;
	int					addr_len;
	struct sockaddr_in	addr;
	int					client_fd;
	size_t				j;

	struct epoll_event event, events[MAX_EVENTS];
	epoll_fd = epoll_create1(0);
	std::vector<Server_conf> servers = conf.getServers();
	for (size_t i = 0; i < servers.size(); i++)
	{
		servers[i].init_server();
		event.events = EPOLLIN;
		event.data.fd = servers[i].get_server().get_server_fd();
		if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD,
				servers[i].get_server().get_server_fd(), &event) == -1)
		{
			std::cerr << strerror(errno) << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	while (1)
	{
		std::cout << "Waiting for connection" << std::endl;
		ndfs = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
		std::cout << "ndfs: " << ndfs << std::endl;
		if (ndfs == -1)
		{
			std::cerr << strerror(errno) << std::endl;
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < ndfs; i++)
		{
			server_status = false;
			for (j = 0; j < servers.size(); j++)
			{
				if (events[i].data.fd == servers[j].get_server().get_server_fd())
				{
					addr_len = servers[j].get_server().get_addrlen();
					addr = servers[j].get_server().get_address();
					client_fd = accept(servers[j].get_server().get_server_fd(),
							(struct sockaddr *)&addr, (socklen_t *)&addr_len);
					if (client_fd < 0)
					{
						std::cerr << strerror(errno) << std::endl;
						continue ;
					}
					event.events = EPOLLIN | EPOLLOUT;
					event.data.fd = client_fd;
					if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) ==
						-1)
					{
						std::cerr << strerror(errno) << std::endl;
						close(client_fd);
						continue ;
					}
					server_status = true;
					break ;
				}
			}
			if (!server_status)
			{
				if (events[i].events)
				{
					handle_client(events[i].data.fd, servers[j]);
				}
				close(events[i].data.fd);
			}
		}
	}
}


int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./webserver <port>" << std::endl;
		return (1);
	}
	Conf conf(av[1]);
	init_servers(conf);
	return (0);
}
