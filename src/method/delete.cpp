/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 19:32:24 by bainur            #+#    #+#             */
/*   Updated: 2024/12/01 22:29:38 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/delete.hpp"

bool delete_request(Request &req, Server_conf &server_c, Response &res)
{
    Location location;
    std::string path;
    int result;

    path = req.get_request_line("Path");
    location = search_location(path, server_c);
    if (location.get_path() != "")
    {
        if (!check_method_right(location.get_method(), "DELETE"))
        {
            res.error_location("Error 405 : Method Not Allowed", 405, location, server_c);
            return (false);
        }
    }
    else
    {
        if (!check_method_right(server_c.get_method(), "DELETE"))
        {
            res.error_basic("Error 405 : Method Not Allowed", 405, server_c);
            return (false);
        }
    }
    if (path.find_last_of("/") == path.size() - 1)
    {
        if (access(path.c_str(), F_OK) == -1)
        {
            res.error_location("Error 403 : Forbidden", 403, location, server_c);
            return (false);
        }
        std::string command = "rm -rf " + path;
		std::cout << "COMMAND => " << command << std::endl;
        if ((result = std::system(command.c_str())) == -1)
        {
            res.error_basic("Error 500 : Internal Server Error", 500, server_c);
            return (false);
        }
    }
    else
    {
        if ((result = std::remove(path.c_str())) != 0)
        {
            res.error_location("Error 404 : Not Found", 404, location, server_c);
            return (false);
        }
    }
    res.set_line("Version", "HTTP/1.1");
    res.set_line("Status", "204");
    res.set_line("Reason-Phrase", "No Content");
    return (true);
}
