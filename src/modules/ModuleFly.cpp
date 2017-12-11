#include <iostream>
#include "ModuleFly.hpp"

void		ModuleFly::update()
{
  std::string	space = "";
  char		idx = 0;

  while (idx < this->_iteration)
    {
      space += "  ";
      ++idx;
    }
  this->_data.clear();
  if (_isActive)
    {
      this->_data.push_back(space + "   ____");
      this->_data.push_back(space + "  ;----\"\"(#)");
      this->_data.push_back(space + "   '--|-|'|'");
      this->_data.push_back(space + "     /  |  \\");
    }
  else
    {
      this->_data.push_back(space + "          _");
      this->_data.push_back(space + " .\"\"\"\"\">.(8)_");
      this->_data.push_back(space + "  `(/_|_\\)\"  \\");
      this->_data.push_back(space + "   /  |  \\    \"");
    }
  if (this->_iteration == ITERATION_MAX)
    this->_iteration = 0;
  else
    this->_iteration += 1;
  this->_isActive = !this->_isActive;
}

ModuleFly::ModuleFly() :
  AModuleText("Dan's fly", 8),
  _isActive(false),
  _iteration(0)
{
  this->update();
}

ModuleFly::~ModuleFly()
{
  ;
}

ModuleFly	&ModuleFly::operator=(ModuleFly const &other)
{
  (void)other;
  return (*this);
}

ModuleFly::ModuleFly(ModuleFly const &other) :
  AModuleText(other._name, other._height)
{
  this->update();
}

