//
// Time.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed May 13 18:01:39 2015 _p dumont
// Last update Wed May 13 18:01:39 2015 _p dumont
//

#ifndef TIME_HH_
# define TIME_HH_

# define USEC_TO_SEC (1000 * 1000)

# include <sys/time.h>

class Time
{
  public:
    Time();
    Time(Time const &t);
    Time &operator =(Time const &t);
    ~Time();

    Time		operator +(Time const &t) const;
    Time		operator -(Time const &t) const;
    Time		operator *(unsigned int i) const;
    Time		operator /(unsigned int i) const;
    Time		&operator +=(Time const &t);
    Time		&operator -=(Time const &t);
    Time		&operator *=(unsigned int i);
    Time		&operator /=(unsigned int i);

    bool		operator ==(Time const &t) const;
    bool		operator !=(Time const &t) const;
    bool		operator >(Time const &t) const;
    bool		operator >=(Time const &t) const;
    bool		operator <(Time const &t) const;
    bool		operator <=(Time const &t) const;

    long long int	toLongLongInt(Time const &t) const;
    double		toDouble(Time const &t) const;
    Time		fromLongLongInt(long long int usec) const;

    long long int	getSecond() const;
    long long int	getMicroSecond() const;

    static Time		microsecond(unsigned long int microsecond);
    static Time		millisecond(unsigned long int millisecond);
    static Time		second(unsigned long int second);
    static Time		minute(unsigned long int minute);
    static Time		hours(unsigned long int hours);

  private:
    timeval		_time;
};

#endif /* !TIME_HH_ */
