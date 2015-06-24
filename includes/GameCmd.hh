//
// GameCmd.hh for GameCmd in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue May 19 19:18:12 2015 g tack
// Last update Tue May 19 19:18:13 2015 g tack
//

#ifndef GAMECMD_HH_
# define GAMECMD_HH_

# include "Button.hh"
# include "KeyConf.hh"
# include "GameState.hh"

class		GameCmd : public GameState
{
  public:
    GameCmd(Game *g);
    virtual ~GameCmd();

    virtual int	update(const Time &diff);
    virtual int	sendEvent(const std::pair<Event, Player *> &event);

  private:
    KeyConf			_k;
    std::vector<Button *>	_buttons;
    Button			*_actual_button;
    unsigned int		_actual_button_id;

    int		waitInput();
};

#endif /* !GAMECMD_HH_ */
