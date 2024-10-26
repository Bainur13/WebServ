/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_index.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:36:58 by bainur            #+#    #+#             */
/*   Updated: 2024/10/26 20:59:34 by bainur           ###   ########.fr       */
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

void auto_index(std::string path, Location &location, Server_conf &server_c, Response &res)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path.c_str());
    if (dir == NULL)
    {
        res.error_location("Error 404 : Not Found", 404, location, server_c);
        return ;
    }
    path = soloslash(path);
    std::string body = "<html>\n<head>\n<title>Index of " + path + "</title>\n</head>\n<body>\n<h1>Index of " + path + "</h1>\n<ul>\n";
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.')
            continue ;
        body += "<li><a href=\"" + path + entry->d_name + "\">" + entry->d_name + "</a></li>\n";
    }
    body += "</ul>\n</body>\n</html>";
    res.set_header("Content-Type", "text/html");
    res.set_body(body);
    closedir(dir);
    return ;
}