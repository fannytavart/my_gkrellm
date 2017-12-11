#ifndef MODULERAM_HPP_
# define MODULERAM_HPP_

# include "AModuleText.hpp"

# define MEMINFO_FILE "/proc/meminfo"

class		ModuleRAM : public AModuleText
{
private:
  void		refreshMemTotal(std::string &memTotal) const;
  void		refreshMemAvailable(std::string &memAvailable) const;
public:
  void		update();
  ModuleRAM(ModuleRAM const &other);
  ModuleRAM();
  ModuleRAM	&operator=(ModuleRAM const &other);
  virtual ~ModuleRAM();
};

#endif
