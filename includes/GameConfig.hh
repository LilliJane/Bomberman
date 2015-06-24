//
// GameConfig.hh for GameConfig in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue May 19 11:39:00 2015 g tack
// Last update Tue May 19 11:39:00 2015 g tack
//

#ifndef GAMECONFIG_HH_
# define GAMECONFIG_HH_

# include <vector>
# include "Button.hh"
# include "GameState.hh"

class		GameConfig : public GameState
{
  public:
    GameConfig(Game *g);
    virtual ~GameConfig();

    virtual int	update(Time const &t);
    virtual int	sendEvent(const std::pair<Event, Player *> &event);

  private:
    bool			_zik;
    std::vector<Button *>	_buttons;
    Button			*_actual_button;
    unsigned int		_actual_button_id;
};

#endif /* !GAMECONFIG_HH_ */
