//
// JoysticListener.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Thu May 14 02:10:57 2015 _p dumont
// Last update Thu May 14 02:10:57 2015 _p dumont
//

#include <sstream>

#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "JoysticListener.hh"

int	JoysticListener::_joystic_guid = 1;


JoysticListener::JoysticListener(Player *p)
  : AEventListener(), _last(None), _t(), _play(p)
{
  std::stringstream ss;

  ss << "/dev/input/js" << this->_joystic_guid++;
  this->_path = ss.str();
  this->_fd = 0;
  for (int i = 0; i < 3; ++i)
    _button[i] = false;
  for (int i = 0; i < 4; ++i)
    _joys[i].first= false;
  _t.reset();
}

JoysticListener::~JoysticListener()
{
  if (this->_fd)
    close(this->_fd);
}

bool		JoysticListener::poolEvent(std::pair<Event, Player *> &e)
{
  static void	(JoysticListener::*tab[])() =
  {
    &JoysticListener::poolButton, &JoysticListener::poolJoys
  };
  char		flush_buffer[1024];
  int		n;

  if (!this->_fd)
    this->tryToOpen();
  else
    {
      while ((n = ::read(_fd, &_pad, sizeof(js_event))) == sizeof(js_event))
	{
	  if ((_pad.type == JS_BUTTON || _pad.type == JS_JOYS))
	    (this->*tab[_pad.type - 1])();
	}
      if (n != -1)
	while (::read(_fd, flush_buffer, 1024) > 0)
	  ;
      if (push_events())
	_t.reset();
    }
  return (AEventListener::poolEvent(e));
}

void		JoysticListener::tryToOpen()
{
  if (this->_fd == 0)
    {
      this->_fd = open(this->_path.c_str(), O_RDONLY | O_NOCTTY | O_NDELAY);
      if (this->_fd == -1)
	this->_fd = 0;
    }
}

int		JoysticListener::push_events()
{
  int		ret;
  std::pair<Event, Player *> tmp;
  static Event	(JoysticListener::*buttonTab[])() =
  {
    &JoysticListener::aEvent, &JoysticListener::bEvent, &JoysticListener::xEvent
  };
  static Event	(JoysticListener::*joysTab[])() const =
  {
    &JoysticListener::leftEvent, &JoysticListener::rightEvent,
    &JoysticListener::upEvent, &JoysticListener::downEvent
  };

  ret = 0;
  tmp.second = this->_play;
  for (unsigned int i = 0; i < 3; ++i)
    if (_button[i])
      {
	tmp.first = (this->*buttonTab[i])();
	this->_events.push(tmp);
      }
  for (unsigned int i = 0; i < 4; ++i)
    {
      if (_t.getElapsedTime() > Time::microsecond(100000))
	{
	  if (_joys[i].first)
	    {
	      tmp.first = (this->*joysTab[i])();
	      this->_events.push(tmp);
	      ret = 1;
	    }
	  else if (!_joys[i].first && _joys[i].second)
	    {
	      --_joys[i].second;
	      tmp.first = (Event)((int)((this->*joysTab[i])()) + 8);
	      this->_events.push(tmp);
	      ret = 1;
	    }
	}
      }
  return (ret);
}

void		JoysticListener::poolButton()
{
  static void	(JoysticListener::* tab[])() =
  {
    &JoysticListener::aButton, &JoysticListener::bButton, &JoysticListener::xButton
  };

  if (_pad.number < 3)
    (this->*tab[_pad.number])();
}

void		JoysticListener::aButton()
{
  if (_pad.value == JS_PRESSED && !_button[JS_A])
    _button[JS_A] = true;
  else if (_pad.value == JS_RELEASE && _button[JS_A])
    _button[JS_A] = false;
}

void		JoysticListener::bButton()
{
  if (_pad.value == JS_PRESSED && !_button[JS_B])
    _button[JS_B] = true;
  else if (_pad.value == JS_RELEASE && _button[JS_B])
    _button[JS_B] = false;
}

void		JoysticListener::xButton()
{
  if (_pad.value == JS_RELEASE && !_button[JS_X])
    _button[JS_X] = true;
}

void		JoysticListener::poolJoys()
{
  int		i;
  bool		value;

  i = 0;
  if (_pad.value > 0)
    ++i;
  if (_pad.number % 2 == 1)
    i += 2;
  if (std::abs(_pad.value) > 15000)
    value = true;
  else
    value = false;

  if (_pad.number <= JS1_Y)
    _joys[i].first = value;
  if (value)
    _joys[i].second = 1;
}

Event		JoysticListener::aEvent()
{
  _button[JS_A] = false;
  return (Enter);
}

Event		JoysticListener::bEvent()
{
  _button[JS_B] = false;
  return (Escape);
}

Event		JoysticListener::xEvent()
{
  _button[JS_X] = false;
  return (PutBomb);
}

Event		JoysticListener::leftEvent() const
{
  return (Left);
}

Event		JoysticListener::rightEvent() const
{
  return (Right);
}

Event		JoysticListener::upEvent() const
{
  return (Up);
}

Event		JoysticListener::downEvent() const
{
  return (Down);
}
