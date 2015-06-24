//
// JoysticListener.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Thu May 14 02:11:12 2015 _p dumont
// Last update Thu May 14 02:11:12 2015 _p dumont
//

#ifndef JOYSTICLISTENER_HPP_
# define JOYSTICLISTENER_HPP_

# include <string>
# include "Player.hh"
# include <linux/joystick.h>

# include "AEventListener.hh"
# include "Timer.hh"

# define JS_BUTTON	1
# define JS_JOYS	2

# define JS_RELEASE	0
# define JS_PRESSED	1

# define JS_LEFT	0
# define JS_RIGHT	1
# define JS_UP		2
# define JS_DOWN	3

# define JS1_X		0
# define JS1_Y		1
# define JS2_X		3
# define JS2_Y		4
# define JS3_X		6
# define JS3_Y		7

# define LT		2
# define RT		5

# define JS_A		0
# define JS_B		1
# define JS_X		2
# define JS_Y		3
# define JS_LB		4
# define JS_RB		5
# define JS_START	6
# define JS_SELECT	7
# define JS_HOME	8

class JoysticListener : public AEventListener
{
  public:
    JoysticListener(Player *p);
    virtual ~JoysticListener();

    virtual bool	poolEvent(std::pair<Event, Player *> &e);

  private:
    void	tryToOpen();
    int		push_events();
    void	poolButton();
    void	poolJoys();

    Event	aEvent();
    Event	bEvent();
    Event	xEvent();

    Event	leftEvent() const;
    Event	rightEvent() const;
    Event	upEvent() const;
    Event	downEvent() const;

    void	aButton();
    void	bButton();
    void	xButton();

    static int	_joystic_guid;

    int		_fd;
    std::string	_path;
    js_event	_pad;
    Event	_last;
    Timer	_t;
    Player	*_play;
    bool	_button[3];
    std::pair<bool, int>	_joys[4];
};

#endif /* !JOYSTICLISTENER_HPP_ */
