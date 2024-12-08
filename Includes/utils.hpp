/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:26:07 by bainur            #+#    #+#             */
/*   Updated: 2024/10/14 16:03:47 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "conf.hpp"
# include <cstdlib>
# include <iostream>
# include <string>

void	error_exit(const std::string &error);
bool	isDigits(const std::string &line);
bool	is_goodport(const std::string &line);
long		ft_atoi_s(std::string str);
bool	check_ip(std::vector<std::string> ip_adress);
bool	is_empty(const std::string &line);
bool	is_server(const std::string &line, std::ifstream &file);
bool	is_location(const std::string &line, std::ifstream &file);
void	error_exit(const std::string &error);
bool	unique_symbol(std::vector<std::string> line_s, std::string c);
std::vector<std::string> split_line(const std::string &line,
	const std::string charset);
std::string read_fd_to_end(int fd);
int send_check(int fd, std::string response);

#endif
