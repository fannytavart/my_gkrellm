#ifndef MODULEELEM_HPP_
# define MODULEELEM_HPP_

# include <string>

class			ModuleElem
{
  bool			_selected;
  std::string const	_name;
public:
  ModuleElem(std::string const &name);
  ~ModuleElem();
  void			setSelected(bool const &selected);
  bool			isSelected() const;
  std::string		getName() const;
};

#endif
