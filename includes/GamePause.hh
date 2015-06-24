//0
// GamePause.hh for GamePause in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Sat Jun 13 14:26:12 2015 g tack
// Last update Sat Jun 13 14:26:12 2015 g tack
//

#ifndef GAMEPAUSE_HH_
# define GAMEPAUSE_HH_

# include <vector>
# include "Button.hh"
# include "GameState.hh"
# include "Save.hh"

class		GamePause : public GameState
{
  public:
    GamePause(Game *g, const Bombermap &map, const std::vector<IA *> &ia);
    virtual ~GamePause();

    virtual int		update(Time const &diff);
    virtual int		sendEvent(const std::pair<Event, Player *> &event);

  private:
    int			saving();

    const Bombermap		&_map;
    const std::vector<IA *>	&_ia;
    std::vector<Button *>	_buttons;
    Button			*_selected_button;
    unsigned int		_actual_button;
};

#endif /* !GAMEPAUSE_HH_ */
