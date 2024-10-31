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

bool Cgi:: executeCgi(std::string &outputToReturn, Request &request)
{
	int		pipefd[2];
	pid_t	pid;
	char buffer[1024];
	ssize_t bytesRead;
	int status;

	if (pipe(pipefd) == -1)
	{
		perror("Erreur creating pipe");
		return (0);
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
	else
	{
		std::string output;
		close(pipefd[1]);
		bytesRead = read(pipefd[0], buffer, 1024);
		while (bytesRead > 0)
		{
			output.append(buffer);
			bytesRead = read(pipefd[0], buffer, 1024);
		}
		close(pipefd[0]);
		waitpid(pid, &status, 0);
		if (status == 1)
			return (1);
		std::cout << "Exit Status du CGI => " << status << std::endl;
		outputToReturn.append(output);
	}
	return (0);
}
Cgi::~Cgi()
{
	;
}
