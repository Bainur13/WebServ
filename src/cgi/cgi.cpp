#include "../../Includes/Cgi.hpp"
#include <assert.h>
#include <cassert>

Cgi::Cgi()
{
	;
}

Cgi::Cgi(const Cgi &copy)
{
	*this = copy;
}

Cgi &Cgi::operator=(const Cgi &copy)
{
	this->_scriptPath = copy._scriptPath;
	this->_interpreterPath = copy._interpreterPath;
	this->_cgiPid = copy._cgiPid;
	this->_cgiFdToRead = copy._cgiFdToRead;
	this->_cgiMethod = copy._cgiMethod;
	this->_clientFd = copy._clientFd;
	return (*this);
}

Cgi::Cgi(std::string path, std::string interpreter)
{
	this->_scriptPath = path;
	this->_interpreterPath = interpreter;
}
void Cgi::setPath(std::string path)
{
	this->_scriptPath = path;
}

void Cgi::setMethod(std::string method)
{
	_cgiMethod = method;
}

Cgi *Cgi::clone()
{
	return new Cgi(*this);
}

void Cgi::setClientFd(int client_fd)
{
	_clientFd = client_fd;
}

std::string Cgi::getMethod()
{
	return _cgiMethod;
}

std::string Cgi::getPath()
{
	return (_scriptPath);
}
void Cgi::setInterpreter(std::string interpreter)
{
	this->_interpreterPath = interpreter;
}
std::string Cgi::getInterpreter()
{
	return (this->_interpreterPath);
}

std::vector<const char*> Cgi::build_env(Request &request)
{
	std::vector<std::string> env;
	std::string method = request.get_request_line("Method");
	env.push_back(this->_scriptPath);
	env.push_back("SCRIPT_NAME=" + this->_scriptPath);
	env.push_back("REQUEST_METHOD=" + method);
	if (method == "GET")
    	env.push_back("QUERY_STRING=" + request.get_url_params(request.get_request_line("Path")));
	if (method == "POST")
	{
		env.push_back("CONTENT_TYPE=" + request.get_request_header("Content-type"));
		env.push_back("CONTENT_LENGTH=" + request.get_request_header("Content-length"));
	}
    env.push_back("HTTP_USER_AGENT=" + request.get_request_header("User-Agent"));

	std::vector<const char*> final_env;

	for (std::vector<std::string>::iterator it = env.begin(); it != env.end(); it++)
	{
		final_env.push_back((*it).c_str());
	}
	final_env.push_back(NULL);
	return (final_env);
}

bool Cgi:: executeCgi(Request &request)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		perror("Erreur creating pipe");
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (execve(this->getPath().c_str(), const_cast<char* const*>(build_env(request).data()), NULL) == -1)
		{
			perror("Erreur lors de l'exécution du script");
			_exit(1);
		}
	}
	else if ( pid > 0)
	{
		close(pipefd[1]);
		this->_cgiFdToRead = pipefd[0];
		this->_cgiPid = pid;
	}
	return (0);
}

int Cgi::getCgiPid()
{
	return this->_cgiPid;
}
int Cgi::getCgiFd()
{
	return this->_cgiFdToRead;
}

int Cgi::getClientFd()
{
	return this->_clientFd;
}

Cgi::~Cgi()
{
	;
}

Cgi *find_cgi_by_client_fd(int client_fd, std::vector<Cgi *> cgis)
{
	for ( std::vector<Cgi *>::iterator it = cgis.begin(); it != cgis.end(); it++)
	{
		if ((*it)->getClientFd() == client_fd)
			return (*it);
	}
	return (NULL);
}

void send_timeout_error(int client_fd, Server_conf server_c)
{
	Response res;

	res.error_basic("Error 504 : Gateway Timeout", 504, server_c);
	std::string response = res.final_response();
	if (send(client_fd, response.c_str(), response.size(), 0) == -1)
	{
		std::cerr << strerror(errno) << std::endl;
		close(client_fd);
		return ;
	}
}
void parse_cgi_res(std::string cgiResponse, Response res)
{
	(void)res;
	std::cout << cgiResponse << std::endl;
}

void send_cgi_response(int client_fd, int cgi_fd)
{
	Response res;
	std::string cgiResponse;
	char buffer[1024];
	ssize_t bytesRead;

	bytesRead = read(cgi_fd, buffer, 1024);
	while (bytesRead > 0)
	{
		cgiResponse.append(buffer);
		bytesRead = read(cgi_fd, buffer, 1024);
	}

	parse_cgi_res(cgiResponse, res);

	std::string response = res.final_response();

	if (send(client_fd, response.c_str(), response.size(), 0) == -1)
	{
		std::cerr << strerror(errno) << std::endl;
		close(client_fd);
		return ;
	}
}

void erase_cgi_from_vector(Server_conf server_c, int client_fd)
{
	std::vector<Cgi *> cgis = server_c.get_cgi();
	for ( std::vector<Cgi *>::iterator it = cgis.begin(); it != cgis.end(); it++)
	{
		if ((*it)->getClientFd() == client_fd)
			delete (*it);
	}
}

int check_cgi_status(int client_fd, Server_conf &server_c)
{
	int pid;
	static int timeout;
	int status;

	Cgi *cgi = find_cgi_by_client_fd(client_fd, server_c.get_cgi());
	if (!cgi)
		return (1);

	pid = waitpid(cgi->getCgiPid(), &status, WNOHANG); // Get the return of waitpid to know if CGI is done;
	if (pid == 0) // if he's not done;
	{
		timeout++;
		if (timeout == 1000000)
		{
			timeout = 0;
			send_timeout_error(client_fd, server_c);
			// TODO Envoyer une erreur dans la reponse si le CGI met trop de temps;
			close(cgi->getCgiFd());
			close(client_fd);
			return (0);
		}
		return (1);
	}
	else // if he is done;
	{
		timeout = 0;
		send_cgi_response(client_fd, cgi->getCgiFd());
		erase_cgi_from_vector(server_c, client_fd);
		close(cgi->getCgiFd());
		close(client_fd);
	}
	return (0);
}
