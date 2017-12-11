#ifndef MODULEDATETIME_HPP_
# define MODULEDATETIME_HPP_

# include "AModuleText.hpp"

class		ModuleDateTime : public AModuleText
{
private:
  void		refreshDate(std::string &date) const;
  void		refreshTime(std::string &time) const;
public:
  void		update();
  ModuleDateTime();
  ModuleDateTime(ModuleDateTime const &other);
  ModuleDateTime	&operator=(ModuleDateTime const &other);
  virtual ~ModuleDateTime();
};

#endif
