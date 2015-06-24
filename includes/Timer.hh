//
// Timer.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed May 13 18:47:46 2015 _p dumont
// Last update Wed May 13 18:47:47 2015 _p dumont
//

#ifndef TIMER_HH_
# define TIMER_HH_

#include "Time.hh"

class Timer
{
  public:
    Timer();
    ~Timer();

    Time		getElapsedTime() const;
    Time		reset();

  private:
    Time		_time;
};

#endif /* !TIMER_HH_ */
