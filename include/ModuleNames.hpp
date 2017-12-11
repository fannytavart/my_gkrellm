#ifndef MODULENAMES_HPP_
# define MODULENAMES_HPP_

# include "AModuleText.hpp"

# define HOSTNAME_FILE "/proc/sys/kernel/hostname"

class		ModuleNames : public AModuleText
{
private:
  char const	**_env;
  void		refreshHostname(std::string &hostname) const;
  void		refreshUsername(std::string &username) const;
public:
  void		update();
  ModuleNames(char const ** const &env);
  ModuleNames(ModuleNames const &other);
  ModuleNames	&operator=(ModuleNames const &other);
  virtual ~ModuleNames();
};

#endif
