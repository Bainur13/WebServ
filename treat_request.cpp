#include "webServ.hpp"

Response	error_page(Response &res)
{
	int	file_fd;

	std::string path = "./index/404.html";
	file_fd = open(path.c_str(), O_RDONLY);
	if (file_fd == -1)
	{
		res.set_line("Status", "500");
		res.set_line("Reason", "Internal Server Error");
		res.set_header("Content-Type", "text/html");
		res.set_body("<html><body><h1>500 Internal Server Error</h1></body></html>");
		return (res);
	}
	res.set_line("Status", "404");
	res.set_line("Reason", "Not Found");
	res.set_header("Content-Type", "text/html");
	res.set_body(read_fd_to_end(file_fd));
	return (res);
}
Response	treat_request(Request req)
{
	Response	res;
	int			file_fd;

	res.set_line("Version", "HTTP/1.1");
	if (req.get_request_line("Method") == "GET")
	{
		std::string path = req.get_request_line("Path");
		if (path == "/")
			path = "/index.html";
		path = "./index" + path;
		file_fd = open(path.c_str(), O_RDONLY);
		if (file_fd == -1)
			return (error_page(res));
		else
		{
			res.set_line("Status", "200");
			res.set_line("Reason", "OK");
			res.set_header("Content-Type", "text/html");
		}
		res.set_body(read_fd_to_end(file_fd));
	}
	return (res);
}
