#include "../../Includes/get.hpp"

bool	get_request(Request &req, Server_conf &server_c, Response &res)
{
	Location	location;
	int			fd;

	std::string path;
	path = req.get_request_line("Path");
	location = search_location(path, server_c);
	if (location.get_path() != "")
	{
		if (!check_method_right(location.get_method(), "GET"))
		{
			res.error_basic("Error 405 : Method Not Allowed", 405, server_c);
			return (false);
		}
		if (location.isdblocation())
		{
			std::ifstream db(location.getdbpath().c_str());
			if (!db.is_open())
			{
				if (errno == ENOENT)
				{
					res.error_basic("Error 404 : Not found", 404, server_c);
					std::cout << "Erreur: " << errno << std::endl;
				}
				else if (errno == EACCES)
				{
					res.error_basic("Error 403 : Forbidden", 403, server_c);
					std::cout << "Erreur: " << errno << std::endl;
				}
				else
				{
					res.error_basic("Error 403 : Internal error", 500, server_c);
					std::cout << "Erreur: " << errno << std::endl;
				}
				return (false);
			}
			std::string password = req.get_request_header("db_password");
			std::cout << "PASSWORD RECUP DANS LE HEADER" << password << std::endl;
			if (password != location.getdbpassword() || password == "")
			{
				res.error_basic("Error 403 : Forbidden", 403, server_c);
				return (false);
			}
			res.set_line("Version", "HTTP/1.1");
			res.set_line("Status", "200");
			res.set_line("Reason", "OK");
			std::string content((std::istreambuf_iterator<char>(db)), std::istreambuf_iterator<char>());
			res.set_body(content);
			res.set_header("Content-Type", "application/json");
			res.set_header("Content-Length", res.get_body_size());
			return (true);
		}
		if (location.get_cgi())
		{
			location.get_cgi()->setMethod("GET");
			location.get_cgi()->executeGetCgi(req);
			server_c.add_cgi(location.get_cgi()->clone());
			res.set_cgi(location.get_cgi());
			res.set_cgiRes(true);
			return (true);
		}
		else if (path.find_last_of("/") == path.size() - 1)
		{
			if (location.get_index() != "")
			{
				path += location.get_index();
				fd = open(path.c_str(), O_RDONLY);
				if (fd < 0)
				{
					res.error_location("Error 404 : Not Found", 404, location, server_c);
					return (false);
				}
				res.set_body(read_fd_to_end(fd));
				close(fd);
			}
			else if (location.get_listing())
			{
				if (auto_index(path, location, server_c, res) == false)
					return (false);
				else
					return (true);
			}
			else
			{
				res.error_location("Error 403 : Forbidden", 403, location, server_c);
				return (false);
			}
		}
		else
		{
			std::cout << "PATH: " << path << std::endl;
			std::cout << path << std::endl;
			fd = open(path.c_str(), O_RDONLY);
			if (fd < 0)
			{
				res.error_location("Error 404 : Not Found", 404, location, server_c);
				return (false);
			}
			res.set_body(read_fd_to_end(fd));
			close(fd);
		}
	}
	else
	{
		if (!check_method_right(server_c.get_method(), "GET"))
		{
			res.error_basic("Error 405 : Method Not Allowed", 405, server_c);
			return (false);
		}
		if (path.find_last_of("/") == path.size() - 1)
		{
			if (server_c.get_index() != "")
			{
				path += server_c.get_index();
				std::cout << path << std::endl;
				fd = open(path.c_str(), O_RDONLY);
				if (fd < 0)
				{
					res.error_basic("Error 404 : Not Found", 404, server_c);
					return (false);
				}
				res.set_body(read_fd_to_end(fd));
				close(fd);
			}
			else
			{
				res.error_basic("Error 403 : Forbidden", 403, server_c);
				return (false);
			}
		}
		else
		{
			fd = open(path.c_str(), O_RDONLY);
			if (fd < 0)
			{
				res.error_basic("Error 404 : Not Found", 404, server_c);
				return (false);
			}
			res.set_body(read_fd_to_end(fd));
			close(fd);
		}
	}
	if (res.get_body_size() == "0")
	{
		res.error_basic("Error 404 : Not Found", 404, server_c);
		return (false);
	}
	res.set_line("Version", "HTTP/1.1");
	if (location.get_cookies().size() != 0)
	{
		for (std::vector<std::string>::iterator it = location.get_cookies().begin(); it != location.get_cookies().end() ; it++)
			res.add_cookie(*it);
	}
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
	res.set_line("Status", "200");
	res.set_line("Reason", "OK");
	res.set_header("Content-Type", get_content_type(path));
	res.set_header("Content-Length", res.get_body_size());
	return (true);
}
