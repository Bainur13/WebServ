#include "../../Includes/post.hpp"
#include <sys/stat.h>

bool	post_request(Request &req, Server_conf &server_c, Response &res)
{
	Location	location;
	int			fd;
	struct stat	info;
    std::string path;
    bool exist = 0;

	path = req.get_request_line("Path");
	std::cout << path << std::endl;
	location = search_location(path, server_c);
	if (location.get_path() != "")
	{
		if (!check_method_right(location.get_method(), "POST"))
		{
			res.error_basic("Error 405 : Method Not Allowed", 405, server_c);
			return (false);
		}
		if (location.get_root() != "")
			path = location.get_root() + path;
	}
	else
	{
		if (!check_method_right(server_c.get_method(), "POST"))
		{
			res.error_basic("Error 405 : Method Not Allowed", 405, server_c);
			return (false);
		}
		if (server_c.get_root() != "")
			path = server_c.get_root() + path;
	}
    if (stat(path.c_str(), &info) == 0)
        exist = 1;
    if ((fd = open(path.c_str(), O_CREAT | O_WRONLY | O_APPEND, 0644)) < 0)
    {
        res.error_basic("Error 500 : Internal Server Error", 500, server_c);
        return (false);
    }
    std::string content_type = req.get_request_line("Content-Type");
    if (content_type == "application/x-www-form-urlencoded")
    {
        std::string body = req.get_request_body();
        write(fd, body.c_str(), body.size());
        if (exist)
            res.error_basic("Error 200 : OK", 200, server_c);
        else
            res.error_basic("Error 201 : Created", 201, server_c);
    }
    else if (content_type == "multipart/form-data")
    {
        std::string boundary = content_type.substr(content_type.find("boundary=") + 9);
        std::string body = req.get_request_body();
        body = body.substr(body.find(boundary) + boundary.size());


    }
	return 1;
}
