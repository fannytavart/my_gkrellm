#include <iostream>
#include <sys/utsname.h>
#include "ModuleOS.hpp"

void			ModuleOS::refreshOS(std::string &os) const
{
  struct utsname	buffer;
  if (uname(&buffer) != 0)
    {
      os = "[Unknown]";
      return ;
    }
  os = buffer.sysname;
}

void			ModuleOS::refreshKernel(std::string &kernel) const
{
  struct utsname	buffer;

  if (uname(&buffer) != 0)
    {
      kernel = "[Unknown]";
      return ;
    }
  kernel = buffer.release;
  kernel += " ";
  kernel += buffer.version;
}

void		ModuleOS::update()
{
  std::string	os;
  std::string	kernel;

  this->refreshOS(os);
  this->refreshKernel(kernel);
  this->_data.clear();
  this->_data.push_back("OS: " + os);
  this->_data.push_back("Kernel: " + kernel);
}

ModuleOS::ModuleOS() :
  AModuleText("OS / Kernel", 6)
{
  this->update();
}

ModuleOS::~ModuleOS()
{
  ;
}

ModuleOS	&ModuleOS::operator=(ModuleOS const &other)
{
  (void)other;
  return (*this);
}

ModuleOS::ModuleOS(ModuleOS const &other) :
  AModuleText(other._name, other._height)
{
  this->update();
}
