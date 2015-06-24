//
// IEventListener.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Thu May 14 02:05:45 2015 _p dumont
// Last update Thu May 14 02:05:46 2015 _p dumont
//

#ifndef AEVENTLISTENER_HH_
# define AEVENTLISTENER_HH_

# include <queue>

# include <linux/input.h>

enum Event
{
  None = 0,
  Escape,
  Disconnect,
  Up,
  Down,
  Right,
  Left,
  PutBomb,
  Enter,  
  Escape_release,
  Disconnect_release,
  Up_release,
  Down_release,
  Right_release,
  Left_release,
  PutBomb_release,
  Enter_release,
  count
};

class Player;

class AEventListener
{
  public:
    AEventListener();
    virtual ~AEventListener() = 0;

    virtual bool	poolEvent(std::pair<Event, Player *> &event);

  protected:
    static unsigned int	_listener_guid;

    std::queue<std::pair<Event, Player *> >	_events;
    unsigned int	_guid;
};

#endif /* !AEVENTLISTENER_HH_ */
