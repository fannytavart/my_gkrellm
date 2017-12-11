#ifndef MODULECPU_HPP_
# define MODULECPU_HPP_

# include "AModuleText.hpp"

# define CPUINFO_FILE "/proc/cpuinfo"
# define LOAD_AVERAGE_FILE "/proc/loadavg"

class		ModuleCPU : public AModuleText
{
private:
  void		refreshLoadAvg(std::string &procUsage, int const &coreNbr) const;
  void		refreshCoreNbr(std::string &coreNbr, int &coreNbrInt) const;
  void		refreshProcModel(std::string &procModel) const;
public:
  void		update();
  ModuleCPU();
  ModuleCPU(ModuleCPU const &other);
  ModuleCPU	&operator=(ModuleCPU const &other);
  virtual ~ModuleCPU();
};

#endif
