/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_index.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:35:38 by bainur            #+#    #+#             */
/*   Updated: 2024/10/31 13:54:04 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_INDEX_HPP
#define AUTO_INDEX_HPP

class Location;

#include "conf.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>


bool auto_index(std::string path, Location &location, Server_conf &server_c, Response &res);

#include "location.hpp"
#endif
