//
// GameMenu.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Fri May 15 03:41:40 2015 _p dumont
// Last update Fri May 15 03:41:41 2015 _p dumont
//

#ifndef GAMEMENU_HH_
# define GAMEMENU_HH_

# include <vector>

# include "GameState.hh"
# include "Button.hh"

class Game;

class GameMenu : public GameState
{
  public:
    GameMenu(Game *game);
    virtual ~GameMenu();

    virtual int		update(Time const &t);
    virtual int		sendEvent(const std::pair<Event, Player *> &event);

  private:
    std::vector<Button *>	_buttons;
    Button			*_selected_button;
    unsigned int		_selected_button_id;
};

#endif /* !GAMEMENU_HH_ */
