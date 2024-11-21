/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:25:57 by bainur            #+#    #+#             */
/*   Updated: 2024/11/21 02:50:50 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/conf.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "../Includes/c-stacktrace.h"


int check_cgi_status(int client_fd, Server_conf &server_c);
Cgi *find_cgi_by_client_fd(int client_fd, std::vector<Cgi *> cgis);

Response	treat_request(Request req, Server_conf &server_c)
{
	Response	res;

	if (req.get_request_line("Method") == "GET")
	{
		if (!get_request(req, server_c, res))
			std::cerr << "Error getting request" << std::endl;
	}
	if (req.get_request_line("Method") == "POST")
	{
		if (!post_request(req, server_c, res))
			std::cerr << "Error posting request" << std::endl;
	}
	if (req.get_request_line("Method") == "DELETE")
	{
		if (!delete_request(req, server_c, res))
			std::cerr << "Error deleting request" << std::endl;
	}
	return (res);
}

void	handle_client(int client_fd, Server_conf &server_c)
{
	Response	res;
	Request		req;

	std::string request;
	request = read_fd_to_end(client_fd);
	if (request.empty())
	{
		close(client_fd);
		return ;
	}
	req.parse_request(request);
	std::cout << "Request received:" << std::endl;
	std::cout << request << std::endl;
	if (req.get_request_body().size() > (uint)server_c.get_sizelimit())
		res.error_basic("Error 413 : Payload Too Large", 413, server_c);
	if (req.get_error() != "")
	{
		std::cerr << req.get_error() << std::endl;
		res.error_basic(req.get_error(), 400, server_c);
	}
	else
		res = treat_request(req, server_c);
	if (res.isCgiRes() == true)
	{
		server_c.get_cgi()[server_c.get_cgi().size() - 1]->setClientFd(client_fd);
	 	return;
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
}

void display_map(const std::map<int, bool>& my_map)
{
    std::map<int, bool>::const_iterator it;
    for (it = my_map.begin(); it != my_map.end(); ++it) {
        std::cout << "Clé : " << it->first << " | Valeur : " << (it->second ? "true" : "false") << std::endl;
    }
}

bool event_being_treated(int fd, std::map<int, bool> *cgi_in_progress)
{
    std::map<int, bool>::iterator it = cgi_in_progress->find(fd);
    if (it != cgi_in_progress->end()) {
        return it->second;
    }
    return false;
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
		std::cout << "Server " << servers[i].get_server_conf_name() << " started" << std::endl;
	}
	std::map<int, bool> cgi_in_progress;
	while (1)
	{
		std::cout << "Waiting for connection" << std::endl;
		ndfs = epoll_wait(epoll_fd, events, MAX_EVENTS, 100);
		std::cout << "ndfs: " << ndfs << std::endl;
		if (ndfs == -1)
		{
			std::cerr << strerror(errno) << std::endl;
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < ndfs; i++)
		{
			int server_conf;
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
					server_conf = j;
					server_status = true;
					break ;
				}
			}
			if (!server_status)
			{
				if ((events[i].events) && !event_being_treated(events[i].data.fd, &cgi_in_progress))
					handle_client(events[i].data.fd, servers[server_conf]);
				int cgi_status = 0;
				if (servers[server_conf].get_cgi().size() > 0)
				{
					cgi_in_progress[events[i].data.fd] = true;
					cgi_status = check_cgi_status(events[i].data.fd, servers[server_conf]);
				}
				if (!cgi_status)
				{
					cgi_in_progress.erase(events[i].data.fd);
					close(events[i].data.fd);
				}
			}
		}
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./webserver <file.conf>" << std::endl;
		return (1);
	}
	init_exceptions(av[0]);
	Conf conf(av[1]);
	init_servers(conf);
	return (0);
}
