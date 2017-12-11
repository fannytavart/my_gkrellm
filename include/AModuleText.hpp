#ifndef AMONITORTEXT_HPP_
# define AMONITORTEXT_HPP_

# include <vector>
# include <iostream>
# include <ncurses.h>
# include "IMonitorModule.hpp"

# define FOCUS_DECORATION '#'
# define ANGLE_DECORATION '+'
# define SIDE_DECORATION '|'
# define TOP_AND_BOTTOM_DECORATION '-'
# define NAME_BOTTOM_DECORATION '='
# define WIDTH_MODULE_TEXT 80

class				AModuleText : public IMonitorModule
{
  bool				_focus;
  bool				_displayStatus;
  WINDOW			*_win;
protected:
  std::string			_name;
  const unsigned int		_height;
  std::vector<std::string>	_data;
public:
  AModuleText(std::string const &name, int const &height) throw();
  bool				isDisplayed() const;
  bool				isFocused() const;
  void				initSubwindows() throw();
  void				drawNameModule() throw();
  void				disableDisplay();
  void				focus();
  void				unfocus();
  void				setDisplayStatus(bool value);
  unsigned int			getHeight();
  void				refreshWindow() throw();
  void				writeData() throw();
  void				truncText(std::string& toTrunc);
  void				mvModule(const unsigned int& posY) throw();
  void				updateDecoration() throw();
  virtual ~AModuleText();
};

#endif
