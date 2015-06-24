//
// ATimeEntity.hh for  in /home/sabour_f/rendu/cpp_bomberman/includes
//
// Made by Florian SABOURIN
// Login   <sabour_f@epitech.net>
//
// Started on  Mon Jun  1 14:22:33 2015 Florian SABOURIN
// Last update Mon Jun  1 14:22:33 2015 Florian SABOURIN
//

#ifndef ATIME_ENTITY_HH_
# define ATIME_ENTITY_HH_

# include "IEntity.hh"
# include "Time.hh"

/*
** Represents an entity on the map on which an action is to be performed at
** a certain time (i.e. bomb)
*/
class ATimeEntity : public IEntity
{
  public:
    ATimeEntity();
    ATimeEntity(const Time &t);
    virtual ~ATimeEntity();

    virtual bool	hasExpired() const;
    virtual void	setTime(const Time &t);
    virtual const Time	&getTime() const;

  protected:
    Time		_end_time;
};

#endif /* !ITIME_ENTITY_HH_ */
