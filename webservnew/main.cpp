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

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "conf.hpp"

void init_servers(Conf &conf)
{
	struct epoll_event event, events[MAX_EVENTS];
	int epoll_fd = epoll_create1(0);
	std::vector<Server_conf> servers = conf.getServers();
	for (size_t i = 0; i < servers.size(); i++)
	{
		servers[i].init_server();
		event.events = EPOLLIN;
		event.data.fd = servers[i].get_server().get_server_fd();
		if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, servers[i].get_server().get_server_fd(), &event) == -1)
		{
			std::cerr << strerror(errno) << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	while (1)
	{
		int ndfs = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
		if (ndfs == -1)
		{
			std::cerr << strerror(errno) << std::endl;
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < ndfs; i++)
		{
			for (size_t j = 0; j < servers.size(); j++)
			{
				if (events[i].data.fd == servers[j].get_server().get_server_fd())
				{
					int addr_len = servers[j].get_server().get_addrlen();
					struct sockaddr_in addr = servers[j].get_server().get_address();
					int client_fd = accept(servers[j].get_server().get_server_fd(), (struct sockaddr *)&addr, (socklen_t *)&addr_len);
					if (client_fd < 0)
					{
						std::cerr << strerror(errno) << std::endl;
						continue;
					}
					event.events = EPOLLIN | EPOLLOUT;
					event.data.fd = client_fd;
					if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) == -1)
					{
						std::cerr << strerror(errno) << std::endl;
						close(client_fd);
						continue;
					}
				}
				else
				{
					char buffer[1024] = {0};
					int valread = read(events[i].data.fd, buffer, 1024);
					if (valread == 0)
					{
						close(events[i].data.fd);
						epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
					}
					else
					{
						std::cout << buffer << std::endl;
					}
				}
			}
		}
	}
}

int main(int ac, char **av)
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
