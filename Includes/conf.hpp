/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:25:52 by bainur            #+#    #+#             */
/*   Updated: 2024/10/31 15:01:23 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_HPP
# define CONF_HPP

# include "Request.hpp"
# include "Response.hpp"
# include "get.hpp"
# include "post.hpp"
# include "delete.hpp"
# include "location.hpp"
# include "server_conf.hpp"
# include "utils_treat.hpp"
# include "auto_index.hpp"
# include <cstdlib>
# include <fcntl.h>
# include <fstream>
# include <iostream>
# include <map>
# include <string>
# include <unistd.h>
# include <vector>

# define EXIT_FAILURE 1

class	Server_conf;
class	Location;

class Conf
{
  public:
	Conf();
	Conf(const std::string &filename);
	Conf(const Conf &copy);

	Conf &operator=(const Conf &copy);

	Server_conf parse_server(std::ifstream &file);
	Location parse_location(std::ifstream &file, std::vector<std::string> line);
	std::vector<Server_conf> getServers() const;
	~Conf();

  private:
	std::vector<Server_conf> _servers_conf;
	void check_servers();
};

#endif
