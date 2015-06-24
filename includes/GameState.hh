//
// GameState.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed May 13 13:39:55 2015 _p dumont
// Last update Wed May 13 13:39:55 2015 _p dumont
//

#ifndef GAMESTATE_HH_
# define GAMESTATE_HH_

# include "Game.hh"
# include "Time.hh"
# include "AEventListener.hh"

class GameState
{
  public:
    GameState(Game *game);
    virtual ~GameState() = 0;

    virtual int		update(Time const &diff) = 0;
    virtual int		sendEvent(std::pair<Event, Player *> const &event) = 0;

  protected:
    Game	*_actual_game;
};

#endif /* !GAMESTATE_HH_ */
