#ifndef MONITORDISPLAY_HPP_
# define MONITORDISPLAY_HPP_

# include <ncurses.h>
# include <stack>
# include "IMonitorModule.hpp"
# include "IMonitorDisplay.hpp"

class				MonitorDisplay : public IMonitorDisplay
{
private:
  SCREEN			*_scr;
  std::list<IMonitorModule*>	_modules;
  std::list<ModuleElem>		_moduleList;
  std::stack<unsigned int>	_idxDeleted;
public:
  MonitorDisplay(char const ** const &env);
  ~MonitorDisplay();
  void				getModulesFromSelector();
  void				loopHandle();
  unsigned int			countDisplayedModule() const;
  bool				deleteModuleFocused();
  void				retrieveModuleDeleted();
  void				selectNextModule();
  void				selectPrevModule();
  void				displayMonitorSelector();
  void				displaySelectorFrame();
  std::list<IMonitorModule*>	&getIMonitorModule();
  void				myAffModule();
  void				exitMonitorSelector();
  bool				handleKey(const int key,
					  std::list<ModuleElem>::iterator &it,
					  unsigned int &y,
					  unsigned int const &x);
  void				handleKeyUp(std::list<ModuleElem>::iterator &it,
					    unsigned int &y,
					    unsigned int const &x);
  void				handleKeyDown(std::list<ModuleElem>::iterator &it,
					      unsigned int &y,
					      unsigned int const &x);
  void				updateModules();
  void				displayModules();
};

#endif
