#ifndef MODULEFLY_HPP_
# define MODULEFLY_HPP_

# include "AModuleText.hpp"

# define ITERATION_MAX (31)

class		ModuleFly : public AModuleText
{
private:
  bool		_isActive;
  char		_iteration;
public:
  void		update();
  ModuleFly();
  ModuleFly(ModuleFly const &other);
  ModuleFly	&operator=(ModuleFly const &other);
  virtual ~ModuleFly();
};

#endif
