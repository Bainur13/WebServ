#include "Cgi.hpp"

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
bool Cgi::executeCgi(std::vector<std::string> argsToPass)
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
	argsToPass.insert(argsToPass.begin(), this->_scriptPath);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (execve(this->_interpreterPath.c_str(), (char *const *)argsToPass.data(),
				NULL) == -1)
		{
			perror("Erreur lors de l'exécution du script");
			_exit(1);
		}
	}
	else
	{
		std::string output;
		close(pipefd[1]);
		while (bytesRead = read(pipefd[0], buffer, 1024) > 0)
		{
			output.append(buffer);
		}
		close(pipefd[0]);
		waitpid(pid, &status, 0);
		std::cout << "Sortie du script" << output << std::endl;
	}
	return (1);
}
Cgi::~Cgi()
{
	;
}
