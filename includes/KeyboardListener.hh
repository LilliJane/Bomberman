//
// KeyboardListener.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Thu May 14 05:12:19 2015 _p dumont
// Last update Thu May 14 05:12:20 2015 _p dumont
//

#ifndef KEYBOARDLISTENER_HH_
# define KEYBOARDLISTENER_HH_

# include "AEventListener.hh"
# include "Player.hh"
# include "SdlContext.hh"

class KeyboardListener : public AEventListener
{
  public:
    KeyboardListener(gdl::SdlContext *ctx, Player *p);
    virtual ~KeyboardListener();

    virtual bool	poolEvent(std::pair<Event, Player *> &event);

  private:
    gdl::SdlContext	*_ctx;
    Player		*_play;
    int			_release[4];
    Timer		_t;
};

#endif /* !KEYBOARDLISTENER_HH_ */
