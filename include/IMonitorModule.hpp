#ifndef IMONITORMODULE_HPP_
# define IMONITORMODULE_HPP_

# include <iostream>

class				IMonitorModule
{
public:
  virtual bool			isDisplayed() const = 0;
  virtual void			update() = 0;
  virtual void			setDisplayStatus(bool value) = 0;
  virtual void			initSubwindows() throw() = 0;
  virtual unsigned int		getHeight() = 0;
  virtual void		       	mvModule(const unsigned int& posY) throw() = 0;
  virtual bool			isFocused() const = 0;
  virtual void			focus() = 0;
  virtual void		       	updateDecoration() throw() = 0;
  virtual void			unfocus() = 0;
  virtual void			refreshWindow() throw() = 0;
  virtual void			writeData() throw() = 0;
  virtual ~IMonitorModule();
};

#endif
