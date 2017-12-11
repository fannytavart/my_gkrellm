/*
** ModuleElem.cpp for ModuleElem in /home/selimrinaz/repo/tek2/Piscine/cpp_gkrellm/include/monitordisplay
** 
** Made by Selim Rinaz
** Login   <selimrinaz@epitech.net>
** 
** Started on  Sat Jan 21 17:46:07 2017 Selim Rinaz
// Last update Sun Jan 22 06:57:25 2017 Ronan Boiteau
*/

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
