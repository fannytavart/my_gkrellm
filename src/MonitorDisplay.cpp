#include <unistd.h>
#include <ncurses.h>
#include <exception>
#include <iostream>
#include <thread>
#include <chrono>
#include "MonitorDisplay.hpp"
#include "ModuleDateTime.hpp"
#include "ModuleOS.hpp"
#include "ModuleNames.hpp"
#include "ModuleCPU.hpp"
#include "ModuleRAM.hpp"
#include "ModuleNetwork.hpp"
#include "ModuleFly.hpp"

MonitorDisplay::MonitorDisplay(char const ** const &env)
{
  if ((this->_scr = newterm(NULL, stdout, stdin)) == NULL)
    _exit(84);
  if (noecho() == ERR)
    _exit(84);
  if (cbreak() == ERR)
    _exit(84);
  if (keypad(stdscr, TRUE) == ERR)
    _exit(84);
  if (curs_set(0) == ERR)
    _exit(84);
  start_color();
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_CYAN);
 
  this->_moduleList.push_back(ModuleElem("NAME"));
  this->_moduleList.push_back(ModuleElem("OS"));
  this->_moduleList.push_back(ModuleElem("DATE TIME"));
  this->_moduleList.push_back(ModuleElem("CPU"));
  this->_moduleList.push_back(ModuleElem("RAM"));
  this->_moduleList.push_back(ModuleElem("NETWORK"));
  this->_moduleList.push_back(ModuleElem("DAN'S FLY"));

  try
    {
      this->_modules.push_back(new ModuleNames(env));
      this->_modules.push_back(new ModuleOS());
      this->_modules.push_back(new ModuleDateTime());
      this->_modules.push_back(new ModuleCPU());
      this->_modules.push_back(new ModuleRAM());
      this->_modules.push_back(new ModuleNetwork());
      this->_modules.push_back(new ModuleFly());
    }
  catch (std::exception e)
    {
      std::cerr << "Failed to instanciate the module list" << std::endl;
      _exit(84);
    }
}

void		MonitorDisplay::getModulesFromSelector()
{
  bool		nothingSelected = true;
  std::list<IMonitorModule*>::iterator itModule = this->_modules.begin();
  for (std::list<ModuleElem>::iterator it = this->_moduleList.begin();
       it != this->_moduleList.end(); ++it, ++itModule)
    {
      if (it->isSelected())
	{
	  (*itModule)->setDisplayStatus(true);
	  nothingSelected = false;
	}
    }
  if (nothingSelected)
    {
      std::cerr << "No modules selected" << std::endl;
      _exit(84);
    }
}

void		MonitorDisplay::handleKeyUp(std::list<ModuleElem>::iterator &it,
					    unsigned int &y,
					    unsigned int const &x)
{
  if (it->isSelected())
    attron(A_STANDOUT);
  mvprintw(y, x, it->getName().c_str());
  attroff(A_STANDOUT);
  if (it == this->_moduleList.begin())
    {
      it = _moduleList.end();
      y = _moduleList.size() + 2;
    }
  else
    --y;
  --it;
}

void		MonitorDisplay::handleKeyDown(std::list<ModuleElem>::iterator &it,
					      unsigned int &y,
					      unsigned int const &x)
{
  if (it->isSelected())
    attron(A_STANDOUT);
  mvprintw(y, x, it->getName().c_str());
  attroff(A_STANDOUT);
  if (y == this->_moduleList.size() + 2)
    {
      it = _moduleList.begin();
      y = 3;
    }
  else
    {
      ++y;
      ++it;
    }
}

bool		MonitorDisplay::handleKey(const int key,
					  std::list<ModuleElem>::iterator &it,
					  unsigned int &y,
					  unsigned int const &x)
{
  if (key == '\n')
    {
      this->exitMonitorSelector();
      return (false);
    }
  else if (key == KEY_UP)
    this->handleKeyUp(it, y, x);
  else if (key == KEY_DOWN)
    this->handleKeyDown(it, y, x);
  else if (key == ' ')
    {
      if (it->isSelected())
	it->setSelected(false);
      else
	it->setSelected(true);
    }
  return (true);
}

void		MonitorDisplay::myAffModule()
{
  int		x;
  int		y;

  x = 2;
  y = 3;
  clear();
  for (std::list<ModuleElem>::iterator reloadAff = this->_moduleList.begin();
       reloadAff != _moduleList.end(); ++reloadAff, ++y)
    {
      if (reloadAff->isSelected())
	attron(A_STANDOUT);
      mvprintw(y, x, reloadAff->getName().c_str());
      attroff(A_STANDOUT);
    }
  refresh();
}

void		MonitorDisplay::displaySelectorFrame()
{
  attron(COLOR_PAIR(1));
  mvprintw(0, 0, "+---------------------+");
  mvprintw(1, 0, "| Select your modules |");
  mvprintw(2, 0, "+---------------------+");
  mvprintw(3, 0, "|");
  mvprintw(3, 22, "|");
  mvprintw(4, 0, "|");
  mvprintw(4, 22, "|");
  mvprintw(5, 0, "|");
  mvprintw(5, 22, "|");
  mvprintw(6, 0, "|");
  mvprintw(6, 22, "|");
  mvprintw(7, 0, "|");
  mvprintw(7, 22, "|");
  mvprintw(8, 0, "|");
  mvprintw(8, 22, "|");
  mvprintw(9, 0, "|");
  mvprintw(9, 22, "|");
  mvprintw(10, 0, "+---------------------+");
  attroff(COLOR_PAIR(1));
}

void				MonitorDisplay::displayMonitorSelector()
{
  unsigned int 			x;
  unsigned int 			y;
  int				key;

  x = 2;
  y = 3;
  this->displaySelectorFrame();
  this->myAffModule();
  for (std::list<ModuleElem>::iterator it = this->_moduleList.begin();
       it != _moduleList.end();)
    {
      this->displaySelectorFrame();
      if (it->isSelected())
	attron(A_STANDOUT);
      attron(COLOR_PAIR(2));
      attron(A_UNDERLINE);
      mvprintw(y, x, it->getName().c_str());
      attroff(A_STANDOUT);
      attroff(COLOR_PAIR(2));
      attroff(A_UNDERLINE);
      refresh();
      key = getch();
      this->displaySelectorFrame();
      this->myAffModule();
      if (this->handleKey(key, it, y, x) == false)
	return ;
    }
}

void		MonitorDisplay::exitMonitorSelector()
{
  if (curs_set(1) == ERR || clear() == ERR || refresh() == ERR)
    _exit(84);
  if (endwin() == ERR)
    _exit(84);
  delscreen(this->_scr);
  this->getModulesFromSelector();
}

MonitorDisplay::~MonitorDisplay()
{
}

std::list<IMonitorModule*>& MonitorDisplay::getIMonitorModule()
{
  return (this->_modules);
}

void		MonitorDisplay::updateModules()
{
  for (std::list<IMonitorModule*>::iterator it = this->_modules.begin();
       it != this->_modules.end(); ++it)
    {
      if ((*it)->isDisplayed() == false)
	continue ;
      try
	{
	  (*it)->update();
	  (*it)->writeData();
	  (*it)->refreshWindow();
	}
      catch (std::runtime_error &e)
	{
	  _exit(84);
	}
    }
}

void		MonitorDisplay::displayModules()
{
  unsigned int y = 0;
  this->displayMonitorSelector();
  if (newterm(NULL, stdout, stdin) == NULL
      || curs_set(0) == ERR
      || clear() == ERR
      || refresh() == ERR)
    _exit(84);
  if (noecho() == ERR)
    _exit(84);
  if (cbreak() == ERR)
    _exit(84);
  if (keypad(stdscr, TRUE) == ERR)
    _exit(84);
  timeout(0);
  unsigned int i = 0;
  for (std::list<IMonitorModule*>::iterator it = this->_modules.begin();
       it != this->_modules.end();
       ++it)
    {
      (*it)->initSubwindows();
      if ((*it)->isDisplayed())
	{
	  if (i == 0)
	    (*it)->focus();
	  (*it)->mvModule(y);
	  y += (*it)->getHeight();
	  ++i;
	}
    }
  refresh();
}

void		MonitorDisplay::retrieveModuleDeleted()
{
  if (this->_idxDeleted.size() == 0)
    return ;
  unsigned int	retrieve = this->_idxDeleted.top();
  this->_idxDeleted.pop();
  unsigned int	idx = 0;
  unsigned int	y = 0;
  for (std::list<IMonitorModule*>::const_iterator itone = this->_modules.begin();
       itone != this->_modules.end();
       ++itone)
    {
      if (idx == retrieve)
	{
	  (*itone)->setDisplayStatus(true);
	  clear();
	  refresh();
	  for (std::list<IMonitorModule*>::iterator it = this->_modules.begin();
	       it != this->_modules.end();
	       ++it)
	    {
	      if ((*it)->isDisplayed())
		{
		  (*it)->mvModule(y);
		  y += (*it)->getHeight();
		}
	    }
	  refresh();
	  return ;
	}
      ++idx;
    }
}

unsigned int	MonitorDisplay::countDisplayedModule() const
{
  unsigned int	idx = 0;
  for (std::list<IMonitorModule*>::const_iterator it = this->_modules.begin();
       it != this->_modules.end();
       ++it)
    {
      if ((*it)->isDisplayed())
	++idx;
    }
  return (idx);
}

void		MonitorDisplay::selectPrevModule()
{
  std::list<IMonitorModule*>::iterator toFocus;
  std::list<IMonitorModule*>::iterator toUnfocus;
  if ((this->countDisplayedModule()) == 1)
    return ;

  std::list<IMonitorModule*>::iterator tmp = this->_modules.begin();
  while (tmp != this->_modules.end())
    {
      if ((*tmp)->isDisplayed() == true)
	break ;
      ++tmp;
    }
  if ((*tmp)->isFocused())
    {
      for (std::list<IMonitorModule*>::iterator findLastDisplayed = this->_modules.begin();
	   findLastDisplayed != this->_modules.end();
	   ++findLastDisplayed)
	{
	  if ((*findLastDisplayed)->isDisplayed())
	    toFocus = findLastDisplayed;
	}
      (*toFocus)->focus();
      (*tmp)->unfocus();
      (*toFocus)->updateDecoration();
      (*tmp)->updateDecoration();
      (*toFocus)->refreshWindow();
      (*tmp)->refreshWindow();      
      return ;
    }
  
  for (std::list<IMonitorModule*>::iterator it = this->_modules.begin();
       it != this->_modules.end();
       ++it)
    {
      if ((*it)->isDisplayed() && (*it)->isFocused() == false)
	toFocus = it;
      
      if ((*it)->isFocused())
	{
	  toUnfocus = it;
	  (*toFocus)->focus();
	  (*toUnfocus)->unfocus();
	  (*toFocus)->updateDecoration();
	  (*toUnfocus)->updateDecoration();
	  (*toFocus)->refreshWindow();
	  (*toUnfocus)->refreshWindow();
	  return ;
	}
    }
}

void		MonitorDisplay::selectNextModule()
{
  unsigned int	idxDisplayedModule = 0;
  unsigned int	nbDisplayedModules;
  std::list<IMonitorModule*>::iterator toFocus;
  std::list<IMonitorModule*>::iterator toUnfocus;
  if ((nbDisplayedModules = this->countDisplayedModule()) == 1)
    return ;
  
  for (std::list<IMonitorModule*>::iterator it = this->_modules.begin();
       it != this->_modules.end();
       ++it)
    {
      if ((*it)->isDisplayed())
	++idxDisplayedModule;
      
      if ((*it)->isFocused())
	{
	  toUnfocus = it;

	  it = (idxDisplayedModule == nbDisplayedModules) ? this->_modules.begin() : ++it;
	  while ((*it)->isDisplayed() == false)
	    ++it;

	  toFocus = it;
	  (*toFocus)->focus();
	  (*toUnfocus)->unfocus();
	  (*toFocus)->updateDecoration();
	  (*toUnfocus)->updateDecoration();
	  (*toFocus)->refreshWindow();
	  (*toUnfocus)->refreshWindow();
	  return ;
	}
    }
}

bool		MonitorDisplay::deleteModuleFocused()
{
  unsigned int y = 0;
  unsigned int idx = 0;
  if ((this->countDisplayedModule()) == 1)
    return (true);
  for (std::list<IMonitorModule*>::iterator it = this->_modules.begin();
       it != this->_modules.end();
       ++it)
    {
      if ((*it)->isFocused())
	{
	  this->_idxDeleted.push(idx);
	  this->selectNextModule();
	  (*it)->setDisplayStatus(false);
	  clear();
	  refresh();
	  for (std::list<IMonitorModule*>::iterator it = this->_modules.begin();
	       it != this->_modules.end();
	       ++it)
	    {
	      if ((*it)->isDisplayed())
		{
		  (*it)->mvModule(y);
		  y += (*it)->getHeight();
		}
	    }
	  refresh();
	  return (false);
	}
      ++idx;
    }
  return (false);
}

void		MonitorDisplay::loopHandle()
{
  bool		need_end = false;
  int		event;
  while (need_end == false)
    {
      event = getch();
      switch (event)
	{
	case ('Z') :
	  retrieveModuleDeleted();
	  break ;
	case ('d'):
	  need_end = deleteModuleFocused();
	  break;
	case (127):
	  need_end = deleteModuleFocused();
	  break;
	case (KEY_UP) :
	  selectPrevModule();
	  break ;
	case (KEY_DOWN) :
	  selectNextModule();
	  break ;
	case ('q'):
	  need_end = true;
	  break ;
	case (27):
	  need_end = true;
	  break ;
	}
      updateModules();
      refresh();
      std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
  endwin();
}

int	main(int ac, char **av, char const **env)
{
  MonitorDisplay	*monitor = new MonitorDisplay(env);
  (void)ac;
  (void)av;
  monitor->displayModules();
  monitor->loopHandle();
  return (0);
}
