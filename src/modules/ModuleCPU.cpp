#include <iostream>
#include <fstream>
#include <sstream>
#include "ModuleCPU.hpp"

void			ModuleCPU::refreshLoadAvg(std::string &procUsage, int const &coreNbr) const
{
  std::string		loadAvgStr;
  char			letter;
  std::ifstream		stream;
  std::ostringstream	stringStream;
  double		procUsageD;
  double		loadAvg;
  
  stream.open(LOAD_AVERAGE_FILE, std::ifstream::in);
  if (!stream.good())
    {
      procUsage = "[Unknown]";
      stream.close();
      return ;
    }
  letter = stream.get();
  while (stream.good() && letter != ' ')
    {
      loadAvgStr += letter;
      letter = stream.get();
    }
  loadAvg = std::stod(loadAvgStr);
  procUsageD = loadAvg * 100 / coreNbr;
  stringStream << procUsageD;
  procUsage = stringStream.str() + "%";
  stream.close();
}

void			ModuleCPU::refreshCoreNbr(std::string &coreNbr, int &coreNbrInt) const
{
  std::string		line;
  std::ifstream		stream;
  std::ostringstream	stringStream;

  coreNbr = "";
  coreNbrInt = 0;
  stream.open(CPUINFO_FILE, std::ifstream::in);
  if (!stream.good())
    {
      coreNbr = "[Unknown]";
      stream.close();
      return ;
    }
  while (std::getline(stream, line))
    {
      if (line.find("processor") != std::string::npos)
	coreNbrInt += 1;
    }
  stream.close();
  stringStream << coreNbrInt;
  coreNbr = stringStream.str();
}

void			ModuleCPU::refreshProcModel(std::string &procModel) const
{
  std::string		line;
  std::ifstream		stream;

  procModel = "";
  stream.open(CPUINFO_FILE, std::ifstream::in);
  if (!stream.good())
    {
      procModel = "[Unknown]";
      stream.close();
      return ;
    }
  while (std::getline(stream, line))
    {
      if (line.find("model name") != std::string::npos)
	{
	  procModel = line;
	  break ;
	}
    }
  stream.close();
  procModel.erase(0, 13);
}

void		ModuleCPU::update()
{
  std::string	procModel;
  std::string	coreNbr;
  int		coreNbrInt;
  std::string	procUsage;

  this->refreshProcModel(procModel);
  this->refreshCoreNbr(coreNbr, coreNbrInt);
  this->refreshLoadAvg(procUsage, coreNbrInt);
  this->_data.clear();
  this->_data.push_back("CPU: " + procModel);
  this->_data.push_back("Number of cores: " + coreNbr);
  this->_data.push_back("Usage: " + procUsage);
}

ModuleCPU::ModuleCPU() :
  AModuleText("CPU", 7)
{
  this->update();
}

ModuleCPU::~ModuleCPU()
{
  ;
}

ModuleCPU	&ModuleCPU::operator=(ModuleCPU const &other)
{
  (void)other;
  return (*this);
}

ModuleCPU::ModuleCPU(ModuleCPU const &other) :
  AModuleText(other._name, other._height)
{
  this->update();
}

