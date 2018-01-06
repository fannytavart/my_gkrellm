#include "ModuleElem.hpp"

ModuleElem::ModuleElem(std::string const &name) :
  _selected(false),
  _name(name)
{
}

ModuleElem::~ModuleElem()
{
}

void		ModuleElem::setSelected(bool const &selected)
{
  this->_selected = selected;
}

bool		ModuleElem::isSelected() const
{
  return (this->_selected);
}

std::string	ModuleElem::getName() const
{
  return (this->_name);
}
