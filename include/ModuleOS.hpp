#ifndef MODULEOS_HPP_
# define MODULEOS_HPP_

# include "AModuleText.hpp"

class		ModuleOS : public AModuleText
{
private:
  void		refreshOS(std::string &date) const;
  void		refreshKernel(std::string &time) const;
public:
  void		update();
  ModuleOS();
  ModuleOS(ModuleOS const &other);
  ModuleOS	&operator=(ModuleOS const &other);
  virtual ~ModuleOS();
};

#endif
