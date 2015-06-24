//
// Timer.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed May 13 18:48:09 2015 _p dumont
// Last update Wed May 13 18:48:09 2015 _p dumont
//

#include "Timer.hh"

Timer::Timer()
{

}

Timer::~Timer()
{

}

Time		Timer::getElapsedTime() const
{
  Time		r;

  r -= this->_time;
  return (r);
}

Time		Timer::reset()
{
  Time		t;
  Time		r;

  r = t - this->_time;
  this->_time = t;
  return (r);
}
