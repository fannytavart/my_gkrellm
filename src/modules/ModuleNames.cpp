#include <iostream>
#include <fstream>
#include "ModuleNames.hpp"

void			ModuleNames::refreshHostname(std::string &hostname) const
{
  std::ifstream		stream;
  char			letter;

  hostname = "";
  stream.open(HOSTNAME_FILE, std::ifstream::in);
  if (!stream.good())
    {
      hostname = "[Unknown]";
      stream.close();
      return ;
    }
  letter = stream.get();
  while (stream.good() && letter != '\n')
    {
      hostname += letter;
      letter = stream.get();
    }
  stream.close();
  return ;
}

static void			my_getenv(char const **env,
					  std::string const &to_find,
					  std::string &result)
{
  size_t			size = 0;
  std::string			tmp;

  while (env[size])
    ++size;
  std::vector<std::string>	vec(env, env + size);
  for (std::vector<std::string>::iterator it = vec.begin() ; it != vec.end() ; ++it)
    {
      tmp = (*it).substr(0, 5);
      if (tmp == to_find)
	result = (*it).substr(5, (*it).size());
    }
}

void	ModuleNames::refreshUsername(std::string &username) const
{
  my_getenv(this->_env, "USER=", username);
}

void		ModuleNames::update()
{
  std::string	hostname;
  std::string	username;

  this->refreshHostname(hostname);
  this->refreshUsername(username);
  this->_data.clear();
  this->_data.push_back("Hostname: " + hostname);
  this->_data.push_back("Username: " + username);
}

ModuleNames::ModuleNames(char const ** const &env) :
  AModuleText("Names", 6)
{
  this->_env = env;
  this->update();
}

ModuleNames::~ModuleNames()
{
  ;
}

ModuleNames	&ModuleNames::operator=(ModuleNames const &other)
{
  (void)other;
  return (*this);
}

ModuleNames::ModuleNames(ModuleNames const &other) :
  AModuleText(other._name, other._height)
{
  this->update();
}

