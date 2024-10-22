/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:26:03 by bainur            #+#    #+#             */
/*   Updated: 2024/10/14 19:18:19 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/utils.hpp"

void	error_exit(const std::string &error)
{
	std::cerr << error << std::endl;
	exit(EXIT_FAILURE);
}

bool	isDigits(const std::string &line)
{
	for (size_t i = 0; i < line.size(); i++)
	{
		if (!isdigit(line[i]))
			return (false);
	}
	return (true);
}

int	ft_atoi_s(std::string str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

bool	is_goodport(const std::string &line)
{
	if (!isDigits(line))
		return (false);
	if (ft_atoi_s(line) < 1024 || ft_atoi_s(line) > 49151)
		return (false);
	return (true);
}

bool	check_ip(std::vector<std::string> ip_adress)
{
	if (ip_adress.size() != 5)
		return (false);
	for (size_t i = 0; i < ip_adress.size(); i++)
	{
		if (!isDigits(ip_adress[i]))
			return (false);
		if (ft_atoi_s(ip_adress[i]) < 0 || ft_atoi_s(ip_adress[i]) > 255)
			return (false);
	}
	return (true);
}

bool	is_empty(const std::string &line)
{
	for (size_t i = 0; i < line.size(); i++)
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r')
			return (false);
	}
	return (true);
}

bool	unique_symbol(std::vector<std::string> line_s, std::string c)
{
	if (line_s.size() != 2)
		return (false);
	if (line_s[0] != c)
		return (false);
	return (true);
}

std::vector<std::string> split_line(const std::string &line, const std::string charset)
{
	std::vector<std::string> line_s;
	std::string word;
	size_t i = 0;

	i = line.find_first_not_of(charset);
	if (i == line.npos)
		return (line_s);
	while (1)
	{
		size_t start = line.find_first_not_of(charset, i);
		if (start == line.npos)
			break;
		size_t end = line.find_first_of(charset, start);
		if (end == line.npos)
			end = line.size();
		word = line.substr(start, end - start);
		line_s.push_back(word);
		i = end;
	}
	line_s.push_back("\0");
	return (line_s);
	
}

bool	is_server(const std::string &line, std::ifstream &file)
{
	std::vector<std::string> line_s;

	line_s = split_line(line, " ");
	if (line_s[0] == "server{")
		return (true);
	if (line_s[0] != "server")
		return (error_exit("Error: server not found"), false);
	if (line_s[1] != "{" && line_s[1] != "\0")
	{
		return (error_exit("Error: server line invalid"), false);
	}
	if (line_s[1] == "\0")
	{
		std::string line_n;
		while (std::getline(file, line_n))
		{
			if (is_empty(line_n))
				continue ;
            if (unique_symbol(split_line(line_n, " "), "{"))
                return (true);
            else
                return (error_exit("Error: server line invalid"), false);
		}
	}
	if (line_s[2] != "\0")
		return (error_exit("Error: server line invalid"), false);
	return (true);
}

bool	is_location(const std::string &line, std::ifstream &file)
{
	std::vector<std::string> line_s;

	line_s = split_line(line, " ");
	if (line_s.size() != 3 && line_s.size() != 4)
		return (false);
	if (line_s[0] != "location")
		return (error_exit("Error: invalid line in server"), false);
	if (line_s[2] != "{" && line_s[2] != "\0")
		return (error_exit("Error: location line invalid"), false);
	if (line_s[2] == "\0")
	{
		std::string line_n;
		while (std::getline(file, line_n))
		{
			if (is_empty(line_n))
				continue ;
            if (unique_symbol(split_line(line_n, " "), "{"))
                return (true);
            else
                return (error_exit("Error: location line invalid"), false);
		}
	}
	if (line_s[3] != "\0")
		return (error_exit("Error: location line invalid"), false);
	return (true);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

std::string read_fd_to_end(int fd)
{
	char	buffer[1024];
	int		valread;

	std::string result;
	result = "";
	while (1)
	{
		valread = read(fd, buffer, 1024);
		if (valread < 0)
		{
			std::cerr << "Error of read / Nothing to read from fd" << std::endl;
			break ;
		}
		if (valread == 0)
			break ;
		buffer[valread] = '\0';
		result += buffer;
		ft_bzero(buffer, 1024);
		if (valread < (int)sizeof(buffer))
			break ;
	}
	return (result);
}

