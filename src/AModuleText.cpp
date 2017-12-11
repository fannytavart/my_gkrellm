# include <curses.h>
#include <stdexcept>
# include "AModuleText.hpp"

AModuleText::AModuleText(std::string const &name, int const &height) throw():
  IMonitorModule(),
  _focus(false),
  _displayStatus(false),
  _name(name),
  _height(height)
{
  if (WIDTH_MODULE_TEXT < 3)
    throw std::runtime_error("No way");
  
  if (this->_name.size() > WIDTH_MODULE_TEXT - 2)
    {
      this->_name.resize(WIDTH_MODULE_TEXT - 2);
      this->_name.replace(this->_name.size() - 3, 3, "...");
    }
}

void	AModuleText::focus()
{
  this->_focus = true;
  this->updateDecoration();
  this->refreshWindow();
}

void AModuleText::unfocus()
{
  this->_focus = false;
  this->updateDecoration();
  this->refreshWindow();
}

void	AModuleText::initSubwindows() throw()
{
  if ((this->_win = newwin(this->_height, WIDTH_MODULE_TEXT + 1, 0, 0)) == NULL)
    throw std::runtime_error("Cannot create subwin");
}

unsigned int	AModuleText::getHeight()
{
  return (this->_height);
}

bool	AModuleText::isDisplayed() const
{
  return (this->_displayStatus);
}

void	AModuleText::setDisplayStatus(bool value)
{
  this->_displayStatus = value;
}

void	AModuleText::updateDecoration() throw()
{
  const char angle_char = (this->_focus == true) ? FOCUS_DECORATION : ANGLE_DECORATION;
  const char side_char = (this->_focus == true) ? FOCUS_DECORATION : SIDE_DECORATION;
  unsigned int	i = 0;
  std::string line;
  std::string line_separator;
  
  wattron(this->_win, COLOR_PAIR(3));
  while (i < WIDTH_MODULE_TEXT - 2)
    {
      line += (this->_focus == true) ? FOCUS_DECORATION : TOP_AND_BOTTOM_DECORATION;
      ++i;
    }
  i = 0;
  while (i < WIDTH_MODULE_TEXT - 2)
    {
      line_separator += (this->_focus == true) ? FOCUS_DECORATION : NAME_BOTTOM_DECORATION;
      ++i;
    }
  if (mvwprintw(this->_win, 0, 0, "%c%s%c", angle_char, line.c_str(), angle_char) == ERR ||
      mvwprintw(this->_win, 1, 0, "%c", side_char) == ERR ||
      mvwprintw(this->_win, 1, WIDTH_MODULE_TEXT - 1, "%c", side_char) == ERR ||
      mvwprintw(this->_win, 2, 0, "%c%s%c", side_char, line_separator.c_str(), side_char) == ERR)
    throw std::runtime_error("printw error");
  i = 0;
  while (i < this->_height - 4)
    {
      if (mvwprintw(this->_win, i + 3, 0, "%c", side_char) == ERR ||
	  mvwprintw(this->_win, i + 3, WIDTH_MODULE_TEXT - 1, "%c", side_char) == ERR)
	throw std::runtime_error("printw error");
      ++i;
    }
  if (mvwprintw(this->_win, i + 3, 0, "%c%s%c", angle_char, line.c_str(), angle_char) == ERR)
    throw std::runtime_error("printw error");
  wattroff(this->_win, COLOR_PAIR(3));
}

bool	AModuleText::isFocused() const
{
  return (this->_focus);
}

void	AModuleText::refreshWindow() throw()
{
  if (wrefresh(this->_win) == ERR)
    throw std::runtime_error("wrefresh");
}

void	AModuleText::truncText(std::string& toTrunc)
{
    if (toTrunc.size() > WIDTH_MODULE_TEXT - 2)
    {
      toTrunc.resize(WIDTH_MODULE_TEXT - 2);
      toTrunc.replace(toTrunc.size() - 3, 3, "...");
    }
}

void	AModuleText::writeData() throw()
{
  unsigned int i = 0;
  std::string empty_line("");
  while (i < WIDTH_MODULE_TEXT - 2)
    {
      empty_line += " ";
      ++i;
    }
  i = 0;
  while (i < this->_height - 4)
    {
      this->truncText(this->_data[i]);

      if (mvwprintw(this->_win, i + 3, 1, "%s", empty_line.c_str()) == ERR
	  || mvwprintw(this->_win, i + 3, 1, "%s", this->_data[i].c_str()) == ERR)
	throw std::runtime_error("printw error");
      ++i;
    }
}

void	AModuleText::drawNameModule() throw()
{
  if (mvwprintw(this->_win, 1, 1, "%s", this->_name.c_str()) == ERR)
    throw std::runtime_error("mvwprintw");
}

void	AModuleText::mvModule(const unsigned int& posY) throw()
{
  if (mvwin(this->_win, posY, 0) == ERR)
    throw std::runtime_error("Cannot move the window");
  try
    {
      wclear(this->_win);
      start_color();
      init_pair(3, COLOR_CYAN, COLOR_BLACK);
      this->updateDecoration();
      this->drawNameModule();
      this->writeData();
      this->refreshWindow();
    }
  catch (std::runtime_error& e)
    {
      throw std::runtime_error("cannot refresh data after moving window");
    }
}

void	AModuleText::disableDisplay()
{
  this->_displayStatus = false;
}

AModuleText::~AModuleText()
{
  ;
}
