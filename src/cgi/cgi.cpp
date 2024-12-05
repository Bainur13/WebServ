#include "../../Includes/Cgi.hpp"
#include <assert.h>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

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
	this->_cgiPid = copy._cgiPid;
	this->_cgiFdToRead = copy._cgiFdToRead;
	this->_cgiMethod = copy._cgiMethod;
	this->_clientFd = copy._clientFd;

	return (*this);
}

Cgi::Cgi(std::string path)
{
	this->_scriptPath = path;
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

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include <vector>
#include <string>
#include <cstdlib> // Pour malloc, free, et strdup
#include <cstring> // Pour strdup

char **Cgi::build_env(Request &request)
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
        env.push_back("CONTENT_TYPE=" + request.get_request_header("Content-Type"));
        env.push_back("CONTENT_LENGTH=" + request.get_request_header("Content-Length"));
    }
    env.push_back("HTTP_COOKIE=" + request.get_request_header("Cookies"));
    env.push_back("HTTP_USER_AGENT=" + request.get_request_header("User-Agent"));

    // Allocation de l'environnement final (+1 pour le pointeur NULL)
    char **final_env = (char **)malloc((env.size() + 1) * sizeof(char *));
    if (!final_env)
    {
        throw std::bad_alloc(); // Gestion d'erreur si malloc échoue
    }

    int i = 0;
    for (std::vector<std::string>::iterator it = env.begin(); it != env.end(); ++it)
    {
        final_env[i] = strdup(it->c_str());
        if (!final_env[i])
        {
            for (int j = 0; j < i; ++j)
                free(final_env[j]);
            free(final_env);
            throw std::bad_alloc();
        }
        i++;
    }
    final_env[i] = NULL;
    return final_env;
}


bool Cgi::executeGetCgi(Request &request)
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1)
    {
        perror("Erreur creating pipe");
        return (1);
    }

    pid = fork();
    if (pid == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        std::vector<const char*> argv;
        argv.push_back(this->_scriptPath.c_str());
        argv.push_back(NULL);
        char **envp = build_env(request);
        if (execve(this->getPath().c_str(), const_cast<char* const*>(argv.data()), const_cast<char* const*>(envp)) == -1)
        {
            perror("Erreur lors de l'exécution du script");
            _exit(1);
        }
    }
    else if (pid > 0)
    {
        close(pipefd[1]);
        this->_cgiFdToRead = pipefd[0];
        this->_cgiPid = pid;
    }
    return (0);
}




bool Cgi:: executePostCgi(Request &request)
{
	int		outpipe[2];
	int		inpipe[2];
	pid_t	pid;

	if (pipe(outpipe) == -1 || pipe(inpipe) == -1)
	{
		perror("Erreur creating pipe");
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(outpipe[1], STDOUT_FILENO);
		close(outpipe[0]);
		close(outpipe[1]);
		dup2(inpipe[0], STDIN_FILENO);
		close(inpipe[1]);
		close(inpipe[0]);
		std::vector<const char*> argv;
        argv.push_back(this->_scriptPath.c_str());
        argv.push_back(NULL);
		char **envp = build_env(request);
		if (execve(this->getPath().c_str(), const_cast<char* const*>(argv.data()), const_cast<char* const*>(envp)) == -1)
		{
			perror("Erreur lors de l'exécution du script");
			_exit(1);
		}
	}
	else if ( pid > 0)
	{
		std::cout << "CONTENU DU BODY" << request.get_request_body() << std::endl;
		write(inpipe[1], request.get_request_body().c_str(), request.get_request_body().size());
		close(inpipe[0]);
		close(inpipe[1]);
		close(outpipe[1]);
		this->_cgiFdToRead = outpipe[0];
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

void set_res_status(std::string line, Response &res)
{
	std::istringstream first_line(line);
	std::string word;

	if (first_line >> word)
		res.set_line("Version", word);

	if (first_line >> word)
		res.set_line("Status", word);

	std::string reason;

	while (first_line >> word)
	{
		if (!reason.empty())
			reason += " ";
		reason += word;
	}

	res.set_line("Reason", reason);
}
void build_res(std::string cgiResponse, Response &res)
{
	std::istringstream tmp_file(cgiResponse);
	std::string line;
	int line_number = 1;
	int is_body = 0;
	std::string body;
	while (std::getline(tmp_file, line))
	{
		if (line.empty())
			is_body = 1;
		if (line_number == 1)
		{
			set_res_status(line, res);
			line_number++;
			continue;
		}
		else if (!is_body)
		{
			std::size_t pos = line.find(":");
			if (pos != std::string::npos)
			{
				std::string key = line.substr(0, pos);
				std::string value = line.substr(pos + 1);

				key.erase(0, key.find_first_not_of(" \t"));
				key.erase(key.find_last_not_of(" \t") + 1);

				value.erase(0, value.find_first_not_of(" \t"));
				value.erase(value.find_last_not_of(" \t") + 1);

				res.set_header(key, value);
			}
		}
		else if (is_body)
			body += line;
		line_number++;
	}
	res.set_body(body);
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

	build_res(cgiResponse, res);

	std::string response = res.final_response();

	if (send(client_fd, response.c_str(), response.size(), 0) == -1)
	{
		std::cerr << strerror(errno) << std::endl;
		close(client_fd);
		return ;
	}
}

void erase_cgi_from_vector(Server_conf& server_c, int client_fd)
{
    std::vector<Cgi*>& cgis = server_c.get_cgi();
    for (std::vector<Cgi*>::iterator it = cgis.begin(); it != cgis.end();)
    {
        if ((*it)->getClientFd() == client_fd)
        {
            delete *it;
            it = cgis.erase(it);
        }
        else
            ++it;
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
			close(cgi->getCgiFd());
			close(client_fd);
			return (0);
		}
		return (1);
	}
	else if (pid > 0)// if he is done;
	{
		timeout = 0;
		send_cgi_response(client_fd, cgi->getCgiFd());
		erase_cgi_from_vector(server_c, client_fd);
		close(cgi->getCgiFd());
		close(client_fd);
	}
	return (0);
}
