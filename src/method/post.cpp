#include "../../Includes/post.hpp"
#include <sys/stat.h>

bool handle_multipart(Request &req, Response &res, Server_conf &server_c, std::string path, Location &location, bool &exist)
{
	std::string content_type = req.get_request_header("Content-Type");
	size_t pos = content_type.find("boundary=");
	std::cout << "content_type" << std::endl;
	std::cout << content_type << std::endl;
	if (pos == std::string::npos)
	{
		if (location.get_path() != "")
			res.error_location("Error 400 : Bad Request", 400, location, server_c);
		else
			res.error_basic("Error 400 : Bad Request", 400, server_c);
		return (false);
	}
	std::string boundary = content_type.substr(pos + 9);

	std::string body = req.get_request_body();
	std::cout << "body" << std::endl;
	std::cout << body << std::endl;
	std::cout << "boundary" << std::endl;
	std::cout << boundary << std::endl;
	if (body.find(boundary + "--") == std::string::npos)
	{
		res.error_location("Error 400 : Bad Request", 400, location, server_c);
		return (false);
	}
	while (1)
	{
		size_t start = body.find(boundary);
		if (start == std::string::npos)
			break;
		size_t end = body.find(boundary, start + boundary.size());
		if (end == std::string::npos)
			break;
		std::string part = body.substr(start + boundary.size(), end - start - boundary.size());
		size_t pos = part.find("\r\n\r\n");
		if (pos == std::string::npos)
		{
			res.error_location("Error 400 : Bad Request", 400, location, server_c);
			return (false);
		}
		std::cout << "part" << std::endl;
		std::cout << part << std::endl;
		std::string header = part.substr(0, pos);
		std::cout << "header" << std::endl;
		std::cout << header << std::endl;

		std::string content = part.substr(pos + 4);
		content = content.substr(0, content.size() - 5);
		pos = header.find("filename=\"");
		if (pos == std::string::npos)
		{
			res.error_location("Error 400 : Bad Request", 400, location, server_c);
			return (false);
		}
		std::string filename = header.substr(pos + 10);
		pos = filename.find("\"");
		if (pos == std::string::npos)
		{
			res.error_location("Error 400 : Bad Request", 400, location, server_c);
			return (false);
		}
		filename = filename.substr(0, pos);
		std::string filepath = path + filename;
		struct stat info;
		if (stat(filepath.c_str(), &info) == 0)
			exist = 1;
		int file_fd = open(filepath.c_str(), O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (file_fd < 0)
		{
			res.error_basic("Error 500 : Internal Server Error", 500, server_c);
			return (false);
		}
		if (write(file_fd, content.c_str(), content.size()) <= 0)
		{
			res.error_basic("Error 500 : Internal Server Error", 500, server_c);
			return (false);
		}
		else
		{
			close(file_fd);
			body = body.substr(end + boundary.size());
		}
	}
	return (true);
}
bool post_request(Request &req, Server_conf &server_c, Response &res)
{
	Location location;
	int fd;
	struct stat info;
	std::string path;
	bool exist = 0;

	path = req.get_request_line("Path");
	location = search_location(path, server_c);
	if (location.get_path() != "")
	{
		if (!check_method_right(location.get_method(), "POST"))
		{
			res.error_location("Error 405 : Method Not Allowed", 405, location, server_c);
			return (false);
		}
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
	if (location.get_cgi())
	{
		location.get_cgi()->setMethod("POST");
		if (location.get_cgi()->executePostCgi(req) == 1)
		{
			res.error_basic("Error 500 : Internal Server Error", 500, server_c);
			return (false);
		}
		server_c.add_cgi(location.get_cgi()->clone());
		res.set_cgi(location.get_cgi());
		res.set_cgiRes(true);
		return (true);
	}
	std::string content_type = req.get_request_header("Content-Type");
	std::cout << "content_type" << std::endl;
	std::cout << content_type << std::endl;
	size_t pos = content_type.find(";");
	if (pos != std::string::npos)
		content_type = content_type.substr(0, pos);
	std::cout << "content_type" << std::endl;
	std::cout << content_type << std::endl;
	if (content_type == "application/x-www-form-urlencoded")
	{
		if (stat(path.c_str(), &info) == 0)
			exist = 1;
		if ((fd = open(path.c_str(), O_CREAT | O_WRONLY | O_APPEND, 0644)) < 0)
		{
			res.error_basic("Error 500 : Internal Server Error", 500, server_c);
			return false;
		}
		std::string body = req.get_request_body();
		if (write(fd, body.c_str(), body.size()) <= 0)
		{
			res.error_basic("Error 500 : Internal Server Error", 500, server_c);
			return false;
		}
		close(fd);
	}
	else if (content_type == "multipart/form-data")
	{
		std::cout << "multipart" << std::endl;
		if (!handle_multipart(req, res, server_c, path, location, exist))
			return (false);
	}
	else
	{
		res.error_basic("Error 400 : Bad Request", 400, server_c);
		return (false);
	}
	if (location.get_cookies().size() != 0)
	{
 		for (std::vector<std::string>::iterator it = location.get_cookies().begin(); it != location.get_cookies().end() ; it++)
		{
			std::cout << "COOKIE TO SEND >> " << (*it) << std::endl;
			res.add_cookie(*it);
		}
	}
	std::cout << location.get_unsetcookies().size() << std::endl;
	if (location.get_unsetcookies().size() != 0)
	{
		for (std::vector<std::string>::iterator it = location.get_unsetcookies().begin(); it != location.get_unsetcookies().end() ; it++)
		{
			res.add_cookietounset(*it);
		}
	}
	if (exist)
		res.set_line("Status", "200");
	else
		res.set_line("Status", "201");
	res.set_line("Version", "HTTP/1.1");
	if (location.get_redirect().first)
	{
		res.set_line("Status", "302");
		res.set_line("Reason", "Found");
		std::ostringstream oss;
		oss << server_c.get_port();
		std::string port = oss.str();
		if (location.get_redirect().second == "form")
			res.set_header("Location", "http://" + server_c.get_domain() + ":" + port + server_c.get_redirect_success_page());
		else if (location.get_redirect().second == "default")
			res.set_header("Location", "http://" + server_c.get_domain() + ":" + port + server_c.get_redirect_default_page());
		return (true);
	}
	res.set_line("Reason", "OK");
	res.set_header("Content-Type", "text/html");
	res.set_header("Content-Length", res.get_body_size());
	return (true);
}
