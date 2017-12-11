#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
#include <ctime>
#include "ModuleDateTime.hpp"

void			ModuleDateTime::refreshDate(std::string &date) const
{
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  std::stringstream	ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d (YY-MM-DD)");
  date = ss.str();
}

void			ModuleDateTime::refreshTime(std::string &time) const
{
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  std::stringstream	ss;
  ss << std::put_time(std::localtime(&in_time_t), "%X (24H)");
  time = ss.str();
}

void		ModuleDateTime::update()
{
  std::string	date;
  std::string	time;

  this->refreshDate(date);
  this->refreshTime(time);
  this->_data.clear();
  this->_data.push_back("Date: " + date);
  this->_data.push_back("Time: " + time);
}

ModuleDateTime::ModuleDateTime() :
  AModuleText("Date / Time", 6)
{
  this->update();
}

ModuleDateTime::~ModuleDateTime()
{
  ;
}

ModuleDateTime	&ModuleDateTime::operator=(ModuleDateTime const &other)
{
  (void)other;
  return (*this);
}

ModuleDateTime::ModuleDateTime(ModuleDateTime const &other) :
  AModuleText(other._name, other._height)
{
  this->update();
}
