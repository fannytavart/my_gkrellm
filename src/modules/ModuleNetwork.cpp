#include <iostream>
#include <dirent.h>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "ModuleNetwork.hpp"

void			ModuleNetwork::refreshNetworkLoad(std::string &bytes, std::string const &stats_dir) const
{
  DIR					*folder;
  dirent				*reader;
  unsigned long long			bytesNumeric = 0;
  std::string				localhost = "lo";
  std::string				file;
  std::vector<std::string>		files;
  std::vector<std::string>::iterator	tmp;
  std::string				line;
  std::ifstream				stream;
  std::ostringstream			stringStream;

  bytes = "";
  if ((folder = opendir(NETWORK_INTERFACES_DIR)) == NULL)
    {
      bytes = "[Unknown]";
      return ;
    }
  while ((reader = readdir(folder)))
    {
      if (reader->d_name[0] != '.')
	files.push_back(reader->d_name);
    }
  tmp = std::find(files.begin(), files.end(), localhost);
  if (tmp != files.end())
    files.erase(tmp);
  for (std::vector<std::string>::iterator it = files.begin() ; it != files.end() ; ++it)
    {
      file = NETWORK_INTERFACES_DIR + *it + stats_dir;
      stream.open(file, std::ifstream::in);
      if (!stream.good())
	{
	  bytes = "[Unknown]";
	  stream.close();
	  closedir(folder);
	  return ;
	}
      std::getline(stream, line);
      bytesNumeric += std::stoull(line);
      stream.close();
    }
  closedir(folder);
  stringStream << bytesNumeric;
  bytes = stringStream.str();
  return ;
}

void		ModuleNetwork::update()
{
  std::string	bytesIn;
  std::string	bytesOut;

  this->refreshNetworkLoad(bytesIn, NETWORK_IN_DIR);
  this->refreshNetworkLoad(bytesOut, NETWORK_OUT_DIR);
  this->_data.clear();
  this->_data.push_back("Data received:\t" + bytesIn + " Bytes");
  this->_data.push_back("Data sent:\t" + bytesOut + " Bytes");
}

ModuleNetwork::ModuleNetwork() :
  AModuleText("Network activity", 6)
{
  this->update();
}

ModuleNetwork::~ModuleNetwork()
{
  ;
}

ModuleNetwork	&ModuleNetwork::operator=(ModuleNetwork const &other)
{
  (void)other;
  return (*this);
}

ModuleNetwork::ModuleNetwork(ModuleNetwork const &other) :
  AModuleText(other._name, other._height)
{
  this->update();
}

