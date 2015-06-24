//
// AEventListener.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Thu May 14 02:05:55 2015 _p dumont
// Last update Thu May 14 02:05:56 2015 _p dumont
//

#include "Player.hh"
#include "AEventListener.hh"

unsigned int	AEventListener::_listener_guid = 0;

AEventListener::AEventListener()
{
  this->_guid = this->_listener_guid++;
}

AEventListener::~AEventListener()
{
}

bool		AEventListener::poolEvent(std::pair<Event, Player *> &event)
{
  if (!this->_events.empty())
    {
      event = this->_events.front();
      this->_events.pop();
      return (true);
    }
  return (false);
}
