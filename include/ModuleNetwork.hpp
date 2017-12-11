#ifndef MODULENETWORK_HPP_
# define MODULENETWORK_HPP_

# include "AModuleText.hpp"

# define NETWORK_INTERFACES_DIR "/sys/class/net/"
# define NETWORK_OUT_DIR "/statistics/tx_bytes"
# define NETWORK_IN_DIR "/statistics/rx_bytes"

class		ModuleNetwork : public AModuleText
{
private:
  void		refreshNetworkLoad(std::string &bytes, std::string const &stats_dir) const;
public:
  void		update();
  ModuleNetwork();
  ModuleNetwork(ModuleNetwork const &other);
  ModuleNetwork	&operator=(ModuleNetwork const &other);
  virtual ~ModuleNetwork();
};

#endif
