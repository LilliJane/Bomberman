//
// ITimeEntity.cpp for  in /home/sabour_f/rendu/cpp_bomberman/src
//
// Made by Florian SABOURIN
// Login   <sabour_f@epitech.net>
//
// Started on  Mon Jun  1 14:22:45 2015 Florian SABOURIN
// Last update Mon Jun  1 14:22:45 2015 Florian SABOURIN
//

#include "ATimeEntity.hh"

ATimeEntity::ATimeEntity() :
  _end_time()
{
}

/*
** Initializes the entity, with its countdown expiring at t
** > t the time the entity will expire
*/
ATimeEntity::ATimeEntity(const Time &t) :
  _end_time(t)
{
}

ATimeEntity::~ATimeEntity()
{
}

/*
** Returns true if the countdown has expired (i.e. the object exploded)
** = true if the countdown has expired, false otherwise
*/
bool		ATimeEntity::hasExpired() const
{
  return (this->_end_time < Time());
}

/*
** Sets the countdown end
** > t the countdown end
*/
void		ATimeEntity::setTime(const Time &t)
{
  this->_end_time = t;
}

/*
** Returns the end of the countdown
** = the end of the countdown
*/
const Time	&ATimeEntity::getTime() const
{
  return (this->_end_time);
}
