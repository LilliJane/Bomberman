//
// EventListener.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed May 13 21:05:54 2015 _p dumont
// Last update Wed May 13 21:05:54 2015 _p dumont
//


#include "Player.hh"
#include "EventListener.hpp"

EventListener::EventListener() :
  AEventListener()
{

}

EventListener::~EventListener()
{
  for (std::vector<AEventListener *>::iterator it = this->_listener.begin();
       it != this->_listener.end();
       ++it)
    delete (*it);
}

bool				EventListener::poolEvent(std::pair<Event, Player *> &event)
{
  std::pair<Event, Player *>	tmp;

  if (!this->_events.empty())
    return (AEventListener::poolEvent(event));

  for (std::vector<AEventListener *>::iterator it = this->_listener.begin();
       it != this->_listener.end();
       ++it)
    {
      if ((*it)->poolEvent(tmp))
	this->_events.push(tmp);
    }
  return (AEventListener::poolEvent(event));
}
