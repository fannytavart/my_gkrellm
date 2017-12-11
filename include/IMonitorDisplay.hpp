#ifndef IMONITORDISPLAY_HPP_
# define IMONITORDISPLAY_HPP_

# include <list>
# include <string>
# include "ModuleElem.hpp"
# include "IMonitorModule.hpp"

class				IMonitorDisplay
{
public:
  virtual ~IMonitorDisplay();
  virtual void			updateModules() = 0;
};

#endif
