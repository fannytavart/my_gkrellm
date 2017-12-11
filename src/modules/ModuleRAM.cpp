#include <iostream>
#include <fstream>
#include <algorithm>
#include "ModuleRAM.hpp"

static bool	isnt_num(char const &letter)
{
  if (letter >= '0' && letter <= '9')
    return (false);
  else
    return (true);
}

void			ModuleRAM::refreshMemAvailable(std::string &memAvailable) const
{
  std::string		line;
  std::ifstream		stream;

  memAvailable = "";
  stream.open(MEMINFO_FILE, std::ifstream::in);
  if (!stream.good())
    {
      memAvailable = "[Unknown]";
      stream.close();
      return ;
    }
  while (std::getline(stream, line))
    {
      if (line.find("MemAvailable:") != std::string::npos)
	{
	  memAvailable = line;
	  stream.close();
	  break ;
	}
    }
  stream.close();
  memAvailable.erase(std::remove_if(memAvailable.begin(), memAvailable.end(), &isnt_num), memAvailable.end());
}

void			ModuleRAM::refreshMemTotal(std::string &memTotal) const
{
  std::string		line;
  std::ifstream		stream;

  memTotal = "";
  stream.open(MEMINFO_FILE, std::ifstream::in);
  if (!stream.good())
    {
      memTotal = "[Unknown]";
      stream.close();
      return ;
    }
  while (std::getline(stream, line))
    {
      if (line.find("MemTotal:") != std::string::npos)
	{
	  memTotal = line;
	  stream.close();
	  break ;
	}
    }
  stream.close();
  memTotal.erase(std::remove_if(memTotal.begin(), memTotal.end(), &isnt_num), memTotal.end());
}

void		ModuleRAM::update()
{
  std::string	memTotal;
  std::string	memAvailable;

  this->refreshMemTotal(memTotal);
  this->refreshMemAvailable(memAvailable);
  this->_data.clear();
  this->_data.push_back("Available memory:\t" + memAvailable + " kB");
  this->_data.push_back("Total memory:\t\t" + memTotal + " kB");
}

ModuleRAM	&ModuleRAM::operator=(ModuleRAM const &other)
{
  (void)other;
  return (*this);
}

ModuleRAM::ModuleRAM(ModuleRAM const &other) :
  AModuleText(other._name, other._height)
{
  this->update();
}

ModuleRAM::ModuleRAM() :
  AModuleText("RAM", 6)
{
  this->update();
}

ModuleRAM::~ModuleRAM()
{
  ;
}
