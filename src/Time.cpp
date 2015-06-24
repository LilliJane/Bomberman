//
// Time.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed May 13 18:01:26 2015 _p dumont
// Last update Wed May 13 18:01:27 2015 _p dumont
//

#include <stdexcept>

#include "Time.hh"

Time::Time()
{
  gettimeofday(&this->_time, 0);
}

Time::Time(Time const &t)
{
  this->_time.tv_sec = t._time.tv_sec;
  this->_time.tv_usec = t._time.tv_usec;
}

Time		&Time::operator =(Time const &t)
{
  this->_time.tv_sec = t._time.tv_sec;
  this->_time.tv_usec = t._time.tv_usec;
  return (*this);
}

Time::~Time()
{

}

Time		Time::operator +(Time const &t) const
{
  return (this->fromLongLongInt(
	    this->toLongLongInt(*this) +
	    this->toLongLongInt(t)));
}

Time		Time::operator -(Time const &t) const
{
  return (this->fromLongLongInt(
	    this->toLongLongInt(*this) -
	    this->toLongLongInt(t)));
}

Time		Time::operator *(unsigned int i) const
{
  return (this->fromLongLongInt(
	    this->toLongLongInt(*this) *
	    i));
}

Time		Time::operator /(unsigned int i) const
{
  if (i == 0)
    throw (std::runtime_error("Division by 0"));
  return (this->fromLongLongInt(
	    this->toLongLongInt(*this) /
	    i));
}

Time		&Time::operator +=(Time const &t)
{
  *this = this->fromLongLongInt(
	this->toLongLongInt(*this) +
	this->toLongLongInt(t));
  return (*this);
}

Time		&Time::operator -=(Time const &t)
{
  *this = this->fromLongLongInt(
	this->toLongLongInt(*this) -
	this->toLongLongInt(t));
  return (*this);
}

Time		&Time::operator *=(unsigned int i)
{
  *this = this->fromLongLongInt(
	this->toLongLongInt(*this) *
	i);
  return (*this);
}

Time		&Time::operator /=(unsigned int i)
{
  if (i == 0)
    throw (std::runtime_error("Division by 0"));
  *this = this->fromLongLongInt(
	this->toLongLongInt(*this) /
	i);
  return (*this);
}

bool		Time::operator ==(Time const &t) const
{
  if (this->_time.tv_sec == t._time.tv_sec &&
      this->_time.tv_usec == t._time.tv_usec)
    return (true);
  return (false);
}

bool		Time::operator !=(Time const &t) const
{
  return (!this->operator ==(t));
}

bool		Time::operator >(Time const &t) const
{
  if (this->toLongLongInt(*this) > this->toLongLongInt(t))
    return (true);
  return (false);
}

bool		Time::operator >=(Time const &t) const
{
  if (this->toLongLongInt(*this) >= this->toLongLongInt(t))
    return (true);
  return (false);
}

bool		Time::operator <(Time const &t) const
{
  if (this->toLongLongInt(*this) < this->toLongLongInt(t))
    return (true);
  return (false);
}

bool		Time::operator <=(Time const &t) const
{
  if (this->toLongLongInt(*this) <= this->toLongLongInt(t))
    return (true);
  return (false);
}

long long int		Time::toLongLongInt(Time const &t) const
{
  return (t._time.tv_usec + t._time.tv_sec * USEC_TO_SEC);
}

double			Time::toDouble(Time const &t) const
{
  double		d;

  d = 0;
  d += t._time.tv_sec;
  d += (double)(t._time.tv_usec) / (double)(USEC_TO_SEC);
  return (d);
}

Time		Time::fromLongLongInt(long long int usec) const
{
  Time		r;

  r._time.tv_sec = usec / USEC_TO_SEC;
  r._time.tv_usec = usec % USEC_TO_SEC;
  return (r);
}

long long int	Time::getSecond() const
{
  return (this->_time.tv_sec);
}

long long int	Time::getMicroSecond() const
{
  return (this->_time.tv_usec);
}

Time		Time::microsecond(unsigned long int microsecond)
{
  Time			t;

  t._time.tv_usec = microsecond % USEC_TO_SEC;
  t._time.tv_sec = microsecond / USEC_TO_SEC;
  return (t);
}

Time		Time::millisecond(unsigned long int millisecond)
{
  Time			t;

  t._time.tv_usec = (millisecond * 1000) % USEC_TO_SEC;
  t._time.tv_sec = (millisecond * 1000) / USEC_TO_SEC;
  return (t);
}

Time		Time::second(unsigned long int second)
{
  Time			t;

  t._time.tv_usec = 0;
  t._time.tv_sec = second;
  return (t);
}

Time		Time::minute(unsigned long int minute)
{
  Time			t;

  t._time.tv_usec = 0;
  t._time.tv_sec = minute * 60;
  return (t);
}

Time		Time::hours(unsigned long int hours)
{
  Time			t;

  t._time.tv_usec = 0;
  t._time.tv_sec = hours * 60 * 60;
  return (t);
}
