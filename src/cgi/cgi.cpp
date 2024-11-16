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
		std::string output;
		close(pipefd[1]);
		this->_cgiFdToRead = pipefd[0];
		this->_cgiPid = pid;
		// bytesRead = read(pipefd[0], buffer, 1024);
		// while (bytesRead > 0)
		// {
		// 	output.append(buffer);
		// 	bytesRead = read(pipefd[0], buffer, 1024);
		// }
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

Cgi::~Cgi()
{
	;
}

int check_cgi_status(int client_fd, Server_conf &server_c)
{
	int pid;
	static int timeout;
	int status;

	pid = waitpid(server_c.get_cgi()[0].getCgiPid(), &status, WNOHANG); // Get the return of waitpid to know if CGI is done;

	if (pid == 0) // if he's not done;
	{
		timeout++;
		if (timeout == 50)
		{
			timeout = 0;
			// TODO Envoyer une erreur dans la reponse si le CGI met trop de temps;
			close(server_c.get_cgi()[0].getCgiFd());
			close(client_fd);
			return (0);
		}
		return (1);
	}
	else // if he is done;
	{
		timeout = 0;
		// std::string cgiResponse;
		// char buffer[1024];
		// ssize_t bytesRead;
		// ? SI le CGI a finit ce qu'il a a faire, construire la reponse avec l'output de celui-ci puis send la reponse au client.
		// bytesRead = read(server_c.get_cgi()[0].getCgiFd(), buffer, 1024);
		// while (bytesRead > 0)
		// {
		// 	cgiReponse.append(buffer);
		// 	bytesRead = read(server_c.get_cgi()[0].getCgiFd(), buffer, 1024);
		// }
		close(server_c.get_cgi()[0].getCgiFd());
		close(client_fd);
	}
	return (0);
}
